#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32_multi_array.hpp>

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include <chrono>

class KeyboardPublisher : public rclcpp::Node
{
public:
    KeyboardPublisher()
    : Node("keyboard_publisher"), stop_flag_(false)
    {
        publisher_ = this->create_publisher<std_msgs::msg::Int32MultiArray>("control_mode_flags", 10);

        // 초기화: [DoB, COM(p), traj(g), payload(t), L1(l), ...]
        flags_ = {0, 0, 0, 0, 0, 0};

        delayed_g_timer_ = this->create_wall_timer(
            std::chrono::seconds(15),
            std::bind(&KeyboardPublisher::delayed_turn_on_g, this)
        );
        delayed_g_timer_->cancel();

        delayed_t_timer_ = this->create_wall_timer(
            std::chrono::seconds(15),
            std::bind(&KeyboardPublisher::delayed_turn_on_t, this)
        );
        delayed_t_timer_->cancel();

        input_thread_ = std::thread(&KeyboardPublisher::keyboard_loop, this);
    }

    ~KeyboardPublisher()
    {
        stop_flag_ = true;
        if (input_thread_.joinable()) {
            input_thread_.join();
        }
    }

private:
    rclcpp::Publisher<std_msgs::msg::Int32MultiArray>::SharedPtr publisher_;
    std::thread input_thread_;
    std::atomic<bool> stop_flag_;
    std::vector<int32_t> flags_;

    // ✅ 동시 접근 보호
    std::mutex flags_mutex_;

    // ✅ p 누른 뒤 예약 타이머들
    rclcpp::TimerBase::SharedPtr delayed_g_timer_;
    rclcpp::TimerBase::SharedPtr delayed_t_timer_;

    void publish_flags_locked()
    {
        // mutex 잡힌 상태에서만 호출한다고 가정
        std_msgs::msg::Int32MultiArray msg;
        msg.data = flags_;
        publisher_->publish(msg);

        std::cout << "[keyboard_teleop_node] Published: [";
        for (size_t i = 0; i < flags_.size(); ++i) {
            std::cout << flags_[i];
            if (i != flags_.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    // ✅ 10초 뒤 실행: p가 아직 ON이면 g ON
    void delayed_turn_on_g()
    {
        std::lock_guard<std::mutex> lock(flags_mutex_);
        delayed_g_timer_->cancel(); // 1회성처럼 사용

        if (flags_.size() >= 3 && flags_[1] == 1) {
            flags_[2] = 1;  // g ON
            std::cout << "[keyboard_teleop_node] (delayed) g turned ON after 45s (p still ON)\n";
            publish_flags_locked();
        } else {
            std::cout << "[keyboard_teleop_node] (delayed) g skipped: p is OFF\n";
        }
    }

    // ✅ 40초 뒤 실행: p가 아직 ON이면 t ON
    void delayed_turn_on_t()
    {
        std::lock_guard<std::mutex> lock(flags_mutex_);
        delayed_t_timer_->cancel(); // 1회성처럼 사용

        if (flags_.size() >= 4 && flags_[1] == 1) {
            // flags_[3] = 1;  // t ON
            std::cout << "[keyboard_teleop_node] (delayed) t turned ON after 15s (p still ON)\n";
            publish_flags_locked();
        } else {
            std::cout << "[keyboard_teleop_node] (delayed) t skipped: p is OFF\n";
        }
    }

    // ✅ p 동작 정의:
    // - OFF -> ON: p 즉시 ON + (10초 후 g ON 예약) + (40초 후 t ON 예약)
    // - ON  -> OFF: p,g,t 즉시 OFF + 예약 취소
    void handle_p_pressed()
    {
        std::lock_guard<std::mutex> lock(flags_mutex_);

        const bool p_is_on = (flags_[1] == 1);

        if (!p_is_on) {
            // OFF -> ON
            flags_[1] = 1;
            std::cout << "[keyboard_teleop_node] p ON (immediate). Scheduling: g ON after 10s, t ON after 40s...\n";

            // 예약 시작
            delayed_g_timer_->reset();
            delayed_t_timer_->reset();

            publish_flags_locked();

        } else {
            // ON -> OFF (요구사항: p,g,t 모두 즉시 OFF)
            flags_[1] = 0;
            flags_[2] = 0;
            flags_[3] = 0;
            std::cout << "[keyboard_teleop_node] p pressed again -> p,g,t OFF (immediate). Cancel delayed events.\n";

            // 예약 취소
            delayed_g_timer_->cancel();
            delayed_t_timer_->cancel();

            publish_flags_locked();
        }
    }

    void keyboard_loop()
    {
        struct termios oldt, newt;
        char ch;

        // 터미널 설정: non-canonical + no echo
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        std::cout
          << "[keyboard_teleop_node] Keys:\n"
          << "  d: toggle DoB\n"
          << "  p: p ON immediately; after 10s -> g ON; after 40s -> t ON; press again -> p,g,t OFF immediately\n"
          << "  g: toggle trajectory (manual)\n"
          << "  t: toggle payload (manual)\n"
          << "  l: toggle L1\n"
          << "  q: quit\n";

        while (!stop_flag_ && rclcpp::ok()) {
            ch = getchar();

            if (ch == '\x1b') {  // ESC 시퀀스(방향키 등) → 무시
                getchar(); // '[' 소비
                getchar(); // 방향키 코드 소비
                continue;
            }

            switch (ch) {
                case 'd': {
                    std::lock_guard<std::mutex> lock(flags_mutex_);
                    flags_[0] = !flags_[0];
                    std::cout << "[keyboard_teleop_node] disturbance_observer_flag = " << flags_[0] << std::endl;
                    publish_flags_locked();
                    break;
                }
                case 'p':
                    handle_p_pressed();
                    break;

                case 'g': {
                    std::lock_guard<std::mutex> lock(flags_mutex_);
                    flags_[2] = !flags_[2];
                    std::cout << "[keyboard_teleop_node] Trajectory Generation = " << flags_[2] << std::endl;
                    publish_flags_locked();
                    break;
                }
                case 't': {
                    std::lock_guard<std::mutex> lock(flags_mutex_);
                    flags_[3] = !flags_[3];
                    std::cout << "[keyboard_teleop_node] Payload Trajectory = " << flags_[3] << std::endl;
                    publish_flags_locked();
                    break;
                }
                case 'l': {
                    std::lock_guard<std::mutex> lock(flags_mutex_);
                    flags_[4] = !flags_[4];
                    std::cout << "[keyboard_teleop_node] L1 Adaptive Controller = " << flags_[4] << std::endl;
                    publish_flags_locked();
                    break;
                }
                case 'q':
                    std::cout << "[keyboard_teleop_node] 'q' pressed. Exiting..." << std::endl;
                    rclcpp::shutdown();
                    break;

                default:
                    std::cout << "[keyboard_teleop_node] Unknown key: '" << ch << "'" << std::endl;
            }
        }

        // 터미널 원복
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<KeyboardPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}