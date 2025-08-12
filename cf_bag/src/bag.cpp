#include "rclcpp/rclcpp.hpp"
#include "rclcpp/executors.hpp"
#include <cstdlib>
#include <memory>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <signal.h>

class BagRecorder : public rclcpp::Node
{
public:
    BagRecorder() : Node("bag_recorder"), bag_directory_("~/rosbags")
    {
        RCLCPP_INFO(this->get_logger(), "Starting bag recording...");
        start_recording();
    }

    ~BagRecorder()
    {
        stop_recording();
    }

private:
    std::string bag_directory_;
    int recording_pid_ = -1;

    std::string get_timestamp()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_struct;
        localtime_r(&now_time, &tm_struct);

        std::ostringstream oss;
        oss << std::put_time(&tm_struct, "%Y%m%d_%H%M%S");
        return oss.str();
    }

    void start_recording()
    {
        // Ensure the directory exists
        std::string mkdir_command = "mkdir -p " + bag_directory_;
        std::system(mkdir_command.c_str());

        // Generate unique filename with timestamp
        std::string timestamp = get_timestamp();
        std::string bag_file = bag_directory_ + "/v3_data_" + timestamp;

        // Start recording process in the background
        std::string command = "ros2 bag record /data_logging_msg -o " + bag_file + " & echo $!";
        FILE* pipe = popen(command.c_str(), "r");
        if (pipe)
        {
            pclose(pipe);
            RCLCPP_INFO(this->get_logger(), "Recording start");
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to start recording");
        }
    }

    void stop_recording()
    {
        if (recording_pid_ > 0)
        {
            std::string stop_command = "kill " + std::to_string(recording_pid_);
            std::system(stop_command.c_str());
            RCLCPP_INFO(this->get_logger(), "Recording stopped.");
        }
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BagRecorder>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
