#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32_multi_array.hpp>

#include <px4_msgs/msg/custom_command_position_mode.hpp>
#include <px4_msgs/msg/custom_command_velocity_mode.hpp>

#include <Eigen/Dense>
#include <chrono>
#include <cmath>
#include <algorithm>  // std::clamp

class TrajectoryPublisher : public rclcpp::Node
{
public:
  TrajectoryPublisher()
  : Node("trajectory_publisher"),
    dt_sim_(0.0)
  {
    // ===================== Tunables =====================
    timer_period_ = 0.005; // 200 Hz

    // ✅ HARD-CODE trajectory type (choose ONE)
    traj_type_ = TrajType::Lissajous;
    // traj_type_ = TrajType::Circle;

    // ramp durations
    alpha_ramp_in_  = 3.0; // [s] ramp-in
    beta_ramp_down_ = 3.0; // [s] ramp-down

    yaw_fixed_ = 0.0;              // [rad]
    vel_feedforward_flag_ = true; // set true if you want to publish vel FF

    // ===================== Publishers =====================
    cmd_pos_pub_ = this->create_publisher<px4_msgs::msg::CustomCommandPositionMode>(
      "/fmu/in/custom_command_position_mode", 10);

    cmd_vel_pub_ = this->create_publisher<px4_msgs::msg::CustomCommandVelocityMode>(
      "/fmu/in/custom_command_velocity_mode", 10);

    // ===================== Subscriber =====================
    rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
    auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 6), qos_profile);

    flags_sub_ = this->create_subscription<std_msgs::msg::Int32MultiArray>(
      "control_mode_flags", qos,
      std::bind(&TrajectoryPublisher::onFlags, this, std::placeholders::_1));

    // ===================== State init =====================
    command_position_.setZero(); // [x, y, z, yaw]
    command_velocity_.setZero(); // [vx, vy, vz, yawrate]
    trajectory_toggle_  = false;
    ramp_down_active_   = false;
    t_disable_          = 0.0;

    // ===================== Timer =====================
    timer_ = this->create_wall_timer(
      std::chrono::duration<double>(timer_period_),
      std::bind(&TrajectoryPublisher::onTimer, this));
  }

private:
  // ====== Trajectory type ======
  enum class TrajType : int {
    Lissajous = 0,
    Circle    = 1
  };

  struct RefState {
    double x{0}, y{0}, z{0};
    double vx{0}, vy{0}, vz{0};
    double yaw{0}, yawrate{0};
  };

  // ----- Flags callback -----
  void onFlags(const std_msgs::msg::Int32MultiArray::SharedPtr msg)
  {
    // idx2 only (trajectory enable)
    if (msg->data.size() < 3) {
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 2000,
                           "control_mode_flags size < 3 (need at least idx2)");
      return;
    }

    const bool new_toggle = (msg->data[2] != 0);

    if (new_toggle != trajectory_toggle_) {
      trajectory_toggle_ = new_toggle;

      if (trajectory_toggle_) {
        // ON: reset time (keep your previous behavior)
        dt_sim_ = 0.0;
        ramp_down_active_ = false;
      } else {
        // OFF: start ramp-down
        ramp_down_active_ = true;
        t_disable_ = dt_sim_;
      }

      RCLCPP_INFO(get_logger(), "Trajectory %s (HARD-CODED type=%s)",
                  trajectory_toggle_ ? "ENABLED" : "DISABLED",
                  (traj_type_ == TrajType::Circle) ? "CIRCLE" : "LISSAJOUS");
    }
  }

  // ----- Main timer -----
  void onTimer()
  {
    dt_sim_ += timer_period_;

    if (trajectory_toggle_) {
      // ON: ramp-in
      trajectory_generate(traj_type_,
                          /*ramp_in_enable=*/true,
                          /*alpha=*/alpha_ramp_in_,
                          /*ramp_down=*/false,
                          /*beta=*/0.0,
                          /*td=*/0.0);

    } else if (ramp_down_active_) {
      // OFF: ramp-down
      const double td = dt_sim_ - t_disable_;

      if (td >= beta_ramp_down_) {
        ramp_down_active_ = false;
        command_position_.setZero();
        command_velocity_.setZero();
      } else {
        trajectory_generate(traj_type_,
                            /*ramp_in_enable=*/false,
                            /*alpha=*/0.0,
                            /*ramp_down=*/true,
                            /*beta=*/beta_ramp_down_,
                            /*td=*/td);
      }

    } else {
      // fully off
      command_position_.setZero();
      command_velocity_.setZero();
    }

    // ---------- publish position ----------
    px4_msgs::msg::CustomCommandPositionMode msg_pos{};
    msg_pos.timestamp = nowToUsec();
    msg_pos.setpoint = {
      static_cast<float>(command_position_(0)),
      static_cast<float>(command_position_(1)),
      static_cast<float>(command_position_(2)),
      static_cast<float>(command_position_(3))
    };
    cmd_pos_pub_->publish(msg_pos);

    // ---------- publish velocity feedforward ----------
    px4_msgs::msg::CustomCommandVelocityMode msg_vel{};
    msg_vel.timestamp = nowToUsec();
    msg_vel.setpoint = {
      static_cast<float>(command_velocity_(0)),
      static_cast<float>(command_velocity_(1)),
      static_cast<float>(command_velocity_(2)),
      static_cast<float>(command_velocity_(3))
    };
    cmd_vel_pub_->publish(msg_vel);
  }

  // ===== Quintic smoothstep helper =====
  static inline void smoothstep_quintic(double tau, double T, double &s, double &s_dot)
  {
    if (T <= 1e-9) {
      s = 1.0;
      s_dot = 0.0;
      return;
    }

    const double t = std::clamp(tau / T, 0.0, 1.0);
    const double t2 = t*t, t3 = t2*t, t4 = t3*t, t5 = t4*t;

    // s = 10t^3 - 15t^4 + 6t^5
    s = 10.0*t3 - 15.0*t4 + 6.0*t5;

    // ds/dt = (30t^2 - 60t^3 + 30t^4) / T
    s_dot = (30.0*t2 - 60.0*t3 + 30.0*t4) / T;
  }

  // ===== Reference generators =====
  RefState make_ref_lissajous(double t) const
  {
    // ====== Tunables (Lissajous) ======
    const double fx = 0.3;   // [Hz]
    const double fy = 0.15;   // [Hz]
    const double fz = 0.6;   // [Hz]

    const double Ax = - 0.15;   // [m]
    const double Ay = 0.35;   // [m]
    const double Az = 0.15;   // [m]

    RefState r{};

    const double wx = 2.0 * M_PI * fx;
    const double wy = 2.0 * M_PI * fy;

    r.x  = Ax * std::sin(wx * t);
    r.vx = Ax * wx * std::cos(wx * t);

    r.y  = Ay * std::sin(wy * t);
    r.vy = Ay * wy * std::cos(wy * t);

    if (Az > 1e-9) {
      const double wz = 2.0 * M_PI * fz;
      r.z  = 0.5 * Az * (std::cos(wz * t) - 1.0);
      r.vz = -0.5 * Az * wz * std::sin(wz * t);
    } else {
      r.z  = 0.0;
      r.vz = 0.0;
    }

    r.yaw = yaw_fixed_;
    r.yawrate = 0.0;
    return r;
  }

  RefState make_ref_circle(double t) const
  {
    // ====== Tunables (Circle) ======
    const double f  = 0.3;   // [Hz]
    const double R  = 0.4;   // [m]
    const double cx = 0.0;    // [m]
    const double cy = 0.0;    // [m]
    const double z0 = 0.0;    // [m]

    RefState r{};
    const double w = 2.0 * M_PI * f;

    r.x  = cx + R * std::cos(w * t);
    r.y  = -cy + R * std::sin(w * t);
    r.z  = z0;

    r.vx = -R * w * std::sin(w * t);
    r.vy = -R * w * std::cos(w * t);
    r.vz = 0.0;

    r.yaw = yaw_fixed_;
    r.yawrate = 0.0;
    return r;
  }

  // ===== Common trajectory generator with ramp-in / ramp-down =====
  void trajectory_generate(TrajType type,
                           bool ramp_in_enable, double alpha,
                           bool ramp_down, double beta, double td)
  {
    const double t = dt_sim_;

    // 1) build reference
    RefState ref{};
    switch (type) {
      case TrajType::Lissajous: ref = make_ref_lissajous(t); break;
      case TrajType::Circle:    ref = make_ref_circle(t);   break;
      default:                  ref = make_ref_lissajous(t); break;
    }

    // 2) ramp scale
    double s = 1.0;
    double s_dot = 0.0;

    if (ramp_down) {
      // ramp-down: 1 -> 0 using s = 1 - p
      double p = 0.0, p_dot = 0.0;
      smoothstep_quintic(td, beta, p, p_dot);
      s = 1.0 - p;
      s_dot = -p_dot;

    } else if (ramp_in_enable) {
      // ramp-in: 0 -> 1
      if (t < alpha) {
        smoothstep_quintic(t, alpha, s, s_dot);
      } else {
        s = 1.0;
        s_dot = 0.0;
      }
    }

    // 3) apply ramp with product rule
    const double x  = s * ref.x;
    const double y  = s * ref.y;
    const double z  = s * ref.z;

    const double vx = s * ref.vx + s_dot * ref.x;
    const double vy = s * ref.vy + s_dot * ref.y;
    const double vz = s * ref.vz + s_dot * ref.z;

    // 4) command output
    command_position_(0) = x;
    command_position_(1) = y;
    command_position_(2) = z;
    command_position_(3) = ref.yaw;

    if (vel_feedforward_flag_) {
      command_velocity_(0) = vx;
      command_velocity_(1) = vy;
      command_velocity_(2) = vz;
      command_velocity_(3) = ref.yawrate;
    } else {
      command_velocity_.setZero();
    }
  }

  // ----- Utils -----
  uint64_t nowToUsec() const
  {
    rclcpp::Clock steady_clock(RCL_STEADY_TIME);
    const auto now = steady_clock.now();
    return static_cast<uint64_t>(now.nanoseconds() / 1000ULL);
  }

  // ----- ROS Interfaces -----
  rclcpp::Publisher<px4_msgs::msg::CustomCommandPositionMode>::SharedPtr cmd_pos_pub_;
  rclcpp::Publisher<px4_msgs::msg::CustomCommandVelocityMode>::SharedPtr cmd_vel_pub_;
  rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr flags_sub_;
  rclcpp::TimerBase::SharedPtr timer_;

  // ----- State -----
  double timer_period_{0.005};
  double dt_sim_{0.0};
  bool trajectory_toggle_{false};

  Eigen::Vector4d command_position_{Eigen::Vector4d::Zero()};
  Eigen::Vector4d command_velocity_{Eigen::Vector4d::Zero()};

  bool   ramp_down_active_{false};
  double t_disable_{0.0};

  // ----- Tunables / Mode -----
  TrajType traj_type_{TrajType::Lissajous};

  double alpha_ramp_in_{3.0};
  double beta_ramp_down_{3.0};

  double yaw_fixed_{0.0};
  bool   vel_feedforward_flag_{false};
};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TrajectoryPublisher>());
  rclcpp::shutdown();
  return 0;
}