#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32_multi_array.hpp>

#include <px4_msgs/msg/custom_command_position_mode.hpp>
#include <px4_msgs/msg/custom_command_velocity_mode.hpp>   // ✅ 추가

#include <Eigen/Dense>
#include <chrono>
#include <cmath>

class TrajectoryPublisher : public rclcpp::Node
{
public:
  TrajectoryPublisher()
  : Node("trajectory_publisher"),
    dt_sim_(0.0)
  {
    // 하드코딩된 주기 (200Hz)
    timer_period_ = 0.005; // [s]

    // ✅ Position publisher
    cmd_pos_pub_ = this->create_publisher<px4_msgs::msg::CustomCommandPositionMode>(
      "/fmu/in/custom_command_position_mode", 10);

    // ✅ Velocity publisher (feedforward)
    cmd_vel_pub_ = this->create_publisher<px4_msgs::msg::CustomCommandVelocityMode>(
      "/fmu/in/custom_command_velocity_mode", 10);

    rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
    auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 6), qos_profile);

    flags_sub_ = this->create_subscription<std_msgs::msg::Int32MultiArray>(
      "control_mode_flags", qos,
      std::bind(&TrajectoryPublisher::onFlags, this, std::placeholders::_1));

    // 상태 초기화
    command_position_.setZero(); // [x, y, z, yaw]
    command_velocity_.setZero(); // [vx, vy, vz, yawrate]  ✅ 추가
    trajectory_toggle_ = false;

    // 타이머: 200hz
    timer_ = this->create_wall_timer(
      std::chrono::duration<double>(timer_period_),
      std::bind(&TrajectoryPublisher::onTimer, this));

  }

private:
  // ----- Callbacks -----
  void onFlags(const std_msgs::msg::Int32MultiArray::SharedPtr msg)
  {
    if (!msg || msg->data.size() < 3) {
      RCLCPP_WARN_THROTTLE(get_logger(), *get_clock(), 2000,
                           "control_mode_flags needs >= 3 elems (DoB, Pos, g).");
      return;
    }

    const bool new_toggle = (msg->data[2] != 0); // g
    if (new_toggle != trajectory_toggle_) {
      trajectory_toggle_ = new_toggle;
      if (trajectory_toggle_) {
        // 켜질 때 시간 리셋 (필요 없으면 주석 처리)
        dt_sim_ = 0.0;
      }
      RCLCPP_INFO(get_logger(), "Trajectory %s",
                  trajectory_toggle_ ? "ENABLED" : "DISABLED");
    }
  }

  void onTimer()
  {
    dt_sim_ += timer_period_;

    if (trajectory_toggle_) {
      // trajectory_generation_with_ff();   // ✅ 리사주 곡선
      trajectory_generation_go_stop();   // ✅ 앞뒤
    } else {
      come_back();
      command_velocity_.setZero();       // ✅ OFF면 FF=0
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
      static_cast<float>(command_velocity_(0)), // vx
      static_cast<float>(command_velocity_(1)), // vy
      static_cast<float>(command_velocity_(2)), // vz
      static_cast<float>(command_velocity_(3))  // yawrate
    };
    cmd_vel_pub_->publish(msg_vel);
  }


  // ✅ Gerono / Lissajous + Z + analytic velocity feedforward
  void trajectory_generation_with_ff()
  {
    // ====== 조절 변수 ======
    const double fx = 0.1;   // [Hz]
    const double fy = 0.2;   // [Hz]
    const double fz = 0.4;   // [Hz]

    const double Ax = 0.3;   // [m]
    const double Ay = 0.15;   // [m]
    const double Az = 0.15;   // [m]

    const double yaw_fixed = 0.0;   // [rad]
    const bool vel_feedforward_flag = false;

    const double t = dt_sim_;

    // ====== X ======
    // x = Ax * sin(2π fx t)
    const double wx = 2.0 * M_PI * fx;
    const double x  = Ax * std::sin(wx * t);
    const double vx = Ax * wx * std::cos(wx * t);

    // ====== Y ======
    // y = Ay * sin(2π fy t)
    const double wy = 2.0 * M_PI * fy;
    const double y  = Ay * std::sin(wy * t);
    const double vy = Ay * wy * std::cos(wy * t);

    // ====== Z ======
    // z = 0.5 * Az * (cos(2π fz t) - 1)
    // vz = - 0.5 * Az * (2π fz) * sin(2π fz t)
    double z  = 0.0;
    double vz = 0.0;
    if (Az > 1e-9) {
      const double wz = 2.0 * M_PI * fz;
      z  = 0.5 * Az * (std::cos(wz * t) - 1.0);
      vz = -0.5 * Az * wz * std::sin(wz * t);
    }

    // ====== yaw / yawrate ======
    const double yaw = yaw_fixed;
    const double yawrate = 0.0;

    // ====== 명령 적용 ======
    command_position_(0) = x;
    command_position_(1) = y;
    command_position_(2) = z;
    command_position_(3) = yaw;

    if (vel_feedforward_flag) {
      command_velocity_(0) = vx;
      command_velocity_(1) = vy;
      command_velocity_(2) = vz;
      command_velocity_(3) = yawrate;
    } else {
      command_velocity_.setZero();
    }
  }

  void trajectory_generation_go_stop()
  {
    // ====== 조절 변수 ======
    const double N = 0.5;        // [m]  이동 거리 (x방향)
    const double n = 1.0;        // [s]  이동(또는 복귀) 시간
    const double period = 6.0;   // [s]  각 이동 끝난 뒤 대기 시간

    const double y_fixed   = 0.0;  // [m]
    const double z_fixed   = 0.0;  // [m]
    const double yaw_fixed = 0.0;  // [rad]

    const bool vel_feedforward_flag = false;  // FF 켜기/끄기
    const double eps = 1e-6;

    // ====== 시간 처리: 반복 사이클 ======
    // 시퀀스: (1) 0->N 이동 n초  (2) N에서 대기 period초
    //        (3) N->0 복귀 n초  (4) 0에서 대기 period초
    const double t = dt_sim_;
    const double n_safe = (n > eps) ? n : eps;
    const double T = 2.0 * n_safe + 2.0 * period;

    // fmod는 음수일 수 있으니 보정
    double tau = std::fmod(t, T);
    if (tau < 0.0) tau += T;

    // ====== 기본값 ======
    double x  = 0.0;
    double vx = 0.0;

    // ====== 구간 경계 ======
    const double t1 = n_safe;             // 이동 끝
    const double t2 = n_safe + period;    // 1차 대기 끝
    const double t3 = 2.0 * n_safe + period; // 복귀 끝
    // const double t4 = T;               // 2차 대기 끝(사이클 끝)

    // ====== piecewise 정의 ======
    if (tau < t1) {
      // (1) 0 -> N : 선형
      vx = N / n_safe;
      x  = vx * tau;
    } else if (tau < t2) {
      // (2) N에서 대기
      vx = 0.0;
      x  = N;
    } else if (tau < t3) {
      // (3) N -> 0 : 선형 복귀
      const double tr = tau - t2;   // 복귀 구간 내부 시간 (0 ~ n)
      vx = -N / n_safe;
      x  = N + vx * tr;             // N - (N/n)*tr
    } else {
      // (4) 0에서 대기
      vx = 0.0;
      x  = 0.0;
    }

    // ====== yaw / yawrate ======
    const double yaw = yaw_fixed;
    const double yawrate = 0.0;

    // ====== 명령 적용 ======
    command_position_(0) = x;
    command_position_(1) = y_fixed;
    command_position_(2) = z_fixed;
    command_position_(3) = yaw;

    if (vel_feedforward_flag) {
      command_velocity_(0) = vx;
      command_velocity_(1) = 0.0;
      command_velocity_(2) = 0.0;
      command_velocity_(3) = yawrate;
    } else {
      command_velocity_.setZero();
    }
  }



  void come_back()
  {
    // TODO: 원점 복귀 로직
    // 예시: 1차 수렴 (discrete-time) — 천천히 (x,y,z,yaw) -> 0 수렴
    const double k = 0.5; // 수렴 속도
    command_position_ -= k * timer_period_ * command_position_;
  }

  // ----- Utils -----
  uint64_t nowToUsec() const
  {
    rclcpp::Clock steady_clock(RCL_STEADY_TIME);  // 별도 클록
    const auto now = steady_clock.now();
    return static_cast<uint64_t>(now.nanoseconds() / 1000ULL);
  }

  // ----- ROS Interfaces -----
  rclcpp::Publisher<px4_msgs::msg::CustomCommandPositionMode>::SharedPtr cmd_pos_pub_;
  rclcpp::Publisher<px4_msgs::msg::CustomCommandVelocityMode>::SharedPtr cmd_vel_pub_; // ✅ 추가
  rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr flags_sub_;
  rclcpp::TimerBase::SharedPtr timer_;

  // ----- State -----
  double timer_period_;       // 고정 주기 [s] (= 0.005)
  double dt_sim_;             // 누적 시뮬레이션 시간 [s]
  bool trajectory_toggle_;    // g 토글 상태 (0: come_back, 1: trajectory_generation)

  Eigen::Vector4d command_position_; // [x, y, z, yaw]
  Eigen::Vector4d command_velocity_; // ✅ 추가

};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TrajectoryPublisher>());
  rclcpp::shutdown();
  return 0;
}
