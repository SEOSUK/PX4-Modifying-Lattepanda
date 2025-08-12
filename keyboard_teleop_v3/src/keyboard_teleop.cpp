#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int32_multi_array.hpp>

#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <thread>
#include <atomic>
#include <vector>

class KeyboardPublisher : public rclcpp::Node
{
public:
    KeyboardPublisher()
    : Node("keyboard_publisher"), stop_flag_(false)
    {
        publisher_ = this->create_publisher<std_msgs::msg::Int32MultiArray>("control_mode_flags", 10);

        // 초기화: [disturbance_observer, position_control, ...] → 모두 0
	
	flags_ = {0, 0, 0, 0, 0, 0};  // [DoB, Pos, LeftArrow, RightArrow, Circle Motion, Sine Motion]
				

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

    void publish_flags()
    {
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

    void keyboard_loop()
    {
        struct termios oldt, newt;
        char ch;
    
        // 터미널 설정: non-canonical + no echo
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
        std::cout << "[keyboard_teleop_node] Press 'd' for DoB, 'p' for COM, 'g' for trajectory, 'q' to quit." << std::endl;
    
        while (!stop_flag_ && rclcpp::ok()) {
            ch = getchar();
    
            if (ch == '\x1b') {  // ESC 시퀀스(방향키 등) → 무시
                getchar(); // '[' 소비
                getchar(); // 방향키 코드 소비
                continue;
            }
    
            switch (ch) {
                case 'd':
                    flags_[0] = !flags_[0];  // toggle
                    std::cout << "[keyboard_teleop_node] disturbance_observer_flag = " << flags_[0] << std::endl;
                    publish_flags();
                    break;
                case 'p':
                    flags_[1] = !flags_[1];  // toggle
                    std::cout << "[keyboard_teleop_node] com_update_flag = " << flags_[1] << std::endl;
                    publish_flags();
                    break;
                case 'g':
                    flags_[2] = !flags_[2];  // toggle
                    std::cout << "[keyboard_teleop_node] Trajectory Generation = " << flags_[2] << std::endl;
                    publish_flags();
                    break;
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

