#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32_multi_array.hpp>
#include <px4_msgs/msg/custom_command_position_mode.hpp>

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
    // 하드코딩된 주기 (50Hz)
    timer_period_ = 0.02; // [s]

    // 퍼블리셔: PX4 커스텀 커맨드
    cmd_pub_ = this->create_publisher<px4_msgs::msg::CustomCommandPositionMode>(
      "/fmu/in/custom_command_position_mode", 10);

      rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
      auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 6), qos_profile);
      
      flags_sub_ = this->create_subscription<std_msgs::msg::Int32MultiArray>(
      "control_mode_flags", qos,
      std::bind(&TrajectoryPublisher::onFlags, this, std::placeholders::_1));

    // 상태 초기화
    command_position_.setZero();    // [x, y, z, yaw]
    trajectory_toggle_ = false;     // 초기엔 꺼짐

    // 타이머: 20ms
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
    // 시뮬레이션 시간 누적 (고정 dt)
    dt_sim_ += timer_period_;

    if (trajectory_toggle_) {
      trajectory_generation();
    } else {
      come_back();
    }

    // 메시지 채우기 & 퍼블리시
    px4_msgs::msg::CustomCommandPositionMode msg{};
    msg.timestamp = nowToUsec();
    msg.setpoint = {
      static_cast<float>(command_position_(0)),
      static_cast<float>(command_position_(1)),
      static_cast<float>(command_position_(2)),
      static_cast<float>(command_position_(3))
    };
    cmd_pub_->publish(msg);
  }

  // ----- Trajectory stubs (나중에 내용 채우기) -----
  void trajectory_generation()
  {
    // TODO: 3차원 뫼비우스의 띠 등 원하는 궤적 수식 넣기
    // 예시(현재는 0 유지):
    command_position_(0) = 0.0; // x
    command_position_(1) += 0.05 * timer_period_; // y
    command_position_(2) = 0.0; // z
    command_position_(3) = 0.0; // yaw
  }

  void come_back()
  {
    // TODO: 원점 복귀 로직
    // 예시: 1차 수렴 (discrete-time) — 천천히 (x,y,z,yaw) -> 0 수렴
    const double k = 2.0; // 수렴 속도
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
  rclcpp::Publisher<px4_msgs::msg::CustomCommandPositionMode>::SharedPtr cmd_pub_;
  rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr flags_sub_;
  rclcpp::TimerBase::SharedPtr timer_;

  // ----- State -----
  double timer_period_;       // 고정 주기 [s] (= 0.02)
  double dt_sim_;             // 누적 시뮬레이션 시간 [s]
  bool trajectory_toggle_;    // g 토글 상태 (0: come_back, 1: trajectory_generation)
  Eigen::Vector4d command_position_; // [x, y, z, yaw]
};

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TrajectoryPublisher>());
  rclcpp::shutdown();
  return 0;
}
