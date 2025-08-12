#include <rclcpp/rclcpp.hpp>
#include "dynamixel_sdk/dynamixel_sdk.h"

#include <cstdint>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <stdexcept>

// ----- Control Table (X-시리즈, Protocol 2.0) -----
static constexpr uint16_t ADDR_TORQUE_ENABLE = 64;
static constexpr uint8_t  TORQUE_DISABLE     = 0;

// 이 노드는 실행되자마자 지정된 ID들에 대해
// 1) Torque OFF -> 2) (옵션) Reboot -> 종료 합니다.
class DynamixelKillReboot : public rclcpp::Node {
public:
  DynamixelKillReboot()
  : Node("dynamixel_kill_reboot")
  {
    // ---- 파라미터 ----
    device_name_   = this->declare_parameter<std::string>("device_name", "/dev/ttyU2D2");
    baudrate_      = this->declare_parameter<int>("baudrate", 1000000);
    protocol_      = this->declare_parameter<double>("protocol", 2.0);

    // ROS2 파라미터의 int 배열은 int64로 들어오므로 변환 필요
    auto ids64     = this->declare_parameter<std::vector<int64_t>>("ids", {1, 2, 3, 4});
    ids_.assign(ids64.begin(), ids64.end());

    reboot_        = this->declare_parameter<bool>("reboot", true);      // true: torque off 후 reboot
    attempts_      = this->declare_parameter<int>("attempts", 2);        // 실패 시 재시도 횟수
    inter_delay_ms_= this->declare_parameter<int>("inter_delay_ms", 50); // 각 서보 간 대기 시간(ms)

    RCLCPP_INFO(get_logger(), "Using port: %s, baud: %d, protocol: %.1f",
                device_name_.c_str(), baudrate_, protocol_);

    // ---- 포트/패킷 핸들러 준비 ----
    port_ = dynamixel::PortHandler::getPortHandler(device_name_.c_str());
    if (!port_->openPort()) {
      RCLCPP_ERROR(get_logger(), "Failed to open port %s", device_name_.c_str());
      throw std::runtime_error("openPort failed");
    }
    if (!port_->setBaudRate(baudrate_)) {
      RCLCPP_ERROR(get_logger(), "Failed to set baudrate %d", baudrate_);
      throw std::runtime_error("setBaudRate failed");
    }

    packet_ = dynamixel::PacketHandler::getPacketHandler(protocol_);

    // ---- 즉시 1회 수행 후 종료 ----
    execute_once_();

    // 깔끔히 종료
    rclcpp::shutdown();
  }

  ~DynamixelKillReboot() override {
    if (port_) {
      port_->closePort(); // private 멤버(is_using_) 접근하지 말 것
    }
  }

private:
  void execute_once_() {
    // 1) 모든 ID Torque OFF
    for (int id : ids_) {
      bool ok = false;
      for (int k = 0; k < attempts_ && !ok; ++k) {
        uint8_t dxl_error = 0;
        int dxl_comm_result =
            packet_->write1ByteTxRx(port_, id, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
        if (dxl_comm_result == COMM_SUCCESS && dxl_error == 0) {
          ok = true;
          RCLCPP_INFO(get_logger(), "[%d] Torque -> DISABLE", id);
        } else {
          RCLCPP_WARN(get_logger(),
                      "[%d] Torque disable failed (comm=%d, err=%u), retry %d/%d",
                      id, dxl_comm_result, dxl_error, k + 1, attempts_);
          std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(inter_delay_ms_));
    }

    // 2) (옵션) Reboot으로 스톨/에러 플래그 초기화
    if (reboot_) {
      for (int id : ids_) {
        bool ok = false;
        for (int k = 0; k < attempts_ && !ok; ++k) {
          uint8_t dxl_error = 0;
          int dxl_comm_result = packet_->reboot(port_, id, &dxl_error);
          if (dxl_comm_result == COMM_SUCCESS && dxl_error == 0) {
            ok = true;
            RCLCPP_INFO(get_logger(), "[%d] Reboot OK", id);
          } else {
            RCLCPP_WARN(get_logger(),
                        "[%d] Reboot failed (comm=%d, err=%u), retry %d/%d",
                        id, dxl_comm_result, dxl_error, k + 1, attempts_);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
          }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(inter_delay_ms_));
      }

      // 리부트 직후 모터 재기동 시간
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    RCLCPP_INFO(get_logger(), "Done. (Torque OFF%s)", reboot_ ? ", rebooted" : "");
  }

  // ---- 파라미터 ----
  std::string device_name_;
  int baudrate_{};
  double protocol_{};
  std::vector<int> ids_;
  bool reboot_{};
  int attempts_{};
  int inter_delay_ms_{};

  // ---- Dynamixel SDK ----
  dynamixel::PortHandler*   port_{nullptr};
  dynamixel::PacketHandler* packet_{nullptr};
};

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  try {
    auto node = std::make_shared<DynamixelKillReboot>();
    rclcpp::spin(node); // execute_once_에서 shutdown 호출 -> 즉시 반환
  } catch (const std::exception& e) {
    fprintf(stderr, "Exception: %s\n", e.what());
  }
  return 0;
}
