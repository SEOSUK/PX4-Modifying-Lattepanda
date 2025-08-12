#include <rclcpp/rclcpp.hpp>
#include "dynamixel_sdk/dynamixel_sdk.h"
#include <cstdio>
#include <cmath>
#include <chrono>
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"

#define DEVICENAME "/dev/ttyU2D2"
#define loop_hz 5000
#define BAUDRATE 1000000
#define PPR 4096
#define PROTOCOL_VERSION 2.0
#define ADDR_TORQUE_ENABLE 64  
#define ADDR_GOAL_POSITION 116
#define ADDR_PRESENT_POSITION 132   
#define ADDR_OPERATING_MODE 11  
#define TORQUE_ENABLE 1
#define TORQUE_DISABLE 0
#define PI 3.14
#define DEG2RAD (PI / 180.0f)
#define RAD2DEG (180.0f / PI)


using namespace std::chrono_literals;

std::chrono::duration<float> delta_t;

//Timer------------------------------------------------
auto end  =std::chrono::high_resolution_clock::now();
auto start=std::chrono::high_resolution_clock::now();


dynamixel::PortHandler *portHandler;
dynamixel::PacketHandler *packetHandler;


int dxl_comm_result = COMM_TX_FAIL;

float T = 0.0;
float period = 8.0;
float omega = 1.0;
float vibration = 0.0;
float th_ang = 0.0;
float th1_cmd = 0.0;
float th2_cmd = 0.0;
float th3_cmd = 0.0;
float th4_cmd = 0.0;
float tray_ang_cmd = 0.f;
uint32_t servo1_ang = 0;
uint32_t servo2_ang = 0;
uint32_t servo3_ang = 0;
uint32_t servo4_ang = 0;
uint32_t servo5_ang = 0;
float amplitude = 0.5;
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //

void CONNECT_dynamixel()
{
    portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    portHandler->openPort();
    portHandler->setBaudRate(BAUDRATE);
}

void SET_dynamixel()
{
    packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

    packetHandler->write1ByteTxRx(portHandler, 1, ADDR_OPERATING_MODE, 3, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 1, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, nullptr);

    packetHandler->write1ByteTxRx(portHandler, 2, ADDR_OPERATING_MODE, 3, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 2, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, nullptr);

    packetHandler->write1ByteTxRx(portHandler, 3, ADDR_OPERATING_MODE, 3, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 3, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, nullptr);

    packetHandler->write1ByteTxRx(portHandler, 4, ADDR_OPERATING_MODE, 3, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 4, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, nullptr);

  //  packetHandler->write1ByteTxRx(portHandler, 10, ADDR_OPERATING_MODE, 4, nullptr);
  //  packetHandler->write1ByteTxRx(portHandler, 10, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, nullptr);

}

void KILL_dynamixel()
{
    packetHandler->write1ByteTxRx(portHandler, 1, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 2, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 3, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 4, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);
   // packetHandler->write1ByteTxRx(portHandler, 10, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);


    portHandler->closePort();
}

float smooth_step_update(float prev_command, float target_command, float alpha)
{
    /*
    float target_deg = 90.0f;  // 예: 사용자가 입력한 목표 각도
    float current_deg = 0.0f;  // 현재 다이나믹셀 명령 상태
    float alpha = 0.05f;       // 느리게 5%씩 추종
    */			       
    return alpha * target_command + (1.0f - alpha) * prev_command;
}

uint16_t RADIAN_TO_TICK(float goal_servo_ang){

  return ((PI+goal_servo_ang)/(2*PI))*PPR;
}

float TICK_TO_RADIAN(uint16_t tick){
  return ((float)tick / (float)PPR) * (2.0f * PI) - PI;
}


void READWRITE_dynamixel()
{
  //if(vibration>=0.3){th_ang = 0.3;}
  //if(vibration<=-0.3){th_ang = -0.3;}

  
  //uint16_t fix_position = 2047;

  std::cout << RADIAN_TO_TICK(th1_cmd) << std::endl;
  packetHandler->write4ByteTxRx(portHandler, 1, ADDR_GOAL_POSITION, RADIAN_TO_TICK(th1_cmd), nullptr);
  packetHandler->write4ByteTxRx(portHandler, 2, ADDR_GOAL_POSITION, RADIAN_TO_TICK(th2_cmd), nullptr);
  packetHandler->write4ByteTxRx(portHandler, 3, ADDR_GOAL_POSITION, RADIAN_TO_TICK(th3_cmd), nullptr);
  packetHandler->write4ByteTxRx(portHandler, 4, ADDR_GOAL_POSITION, RADIAN_TO_TICK(th4_cmd), nullptr);
  //packetHandler->write4ByteTxRx(portHandler, 10, ADDR_GOAL_POSITION, RADIAN_TO_TICK(smooth_step_update(TICK_TO_RADIAN(servo5_ang), tray_ang_cmd, 0.5f)), nullptr);
 // packetHandler->write4ByteTxRx(portHandler, 10, ADDR_GOAL_POSITION, RADIAN_TO_TICK(tray_ang_cmd), nullptr);
  // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //


  packetHandler->read4ByteTxRx(portHandler,1,ADDR_PRESENT_POSITION,&servo1_ang,nullptr);
  packetHandler->read4ByteTxRx(portHandler,2,ADDR_PRESENT_POSITION,&servo2_ang,nullptr);
  packetHandler->read4ByteTxRx(portHandler,3,ADDR_PRESENT_POSITION,&servo3_ang,nullptr);
  packetHandler->read4ByteTxRx(portHandler,4,ADDR_PRESENT_POSITION,&servo4_ang,nullptr);
//  packetHandler->read4ByteTxRx(portHandler,10,ADDR_PRESENT_POSITION,&servo5_ang,nullptr);

  //printf(" servo1_angle | %u\n servo2_angle | %u\n servo3_angle | %u\n servo4_angle | %u\n"
  //  ,servo1_ang,servo2_ang,servo3_ang,servo4_ang);
}


class DynamixelFix : public rclcpp::Node
{
public:
        DynamixelFix() : Node("DynamixelFix")
        {

                rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
                auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);


                CONNECT_dynamixel();
                SET_dynamixel();


                _servo_angle_pub = this->create_publisher<std_msgs::msg::Float32MultiArray>("servo_angle", 10);

                _servo_angle_cmd_sub = this->create_subscription<std_msgs::msg::Float32MultiArray>("servo_angle_cmd", qos,
                [this](const std_msgs::msg::Float32MultiArray::UniquePtr msg) {

                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //

                        th1_cmd = msg->data[0];
                        th2_cmd = msg->data[1];
                        th3_cmd = msg->data[2];
                        th4_cmd = msg->data[3];
//			tray_ang_cmd = msg->data[4];


                });



                auto timer_callback = [this]()->void {

                        READWRITE_dynamixel();


                        std_msgs::msg::Float32MultiArray servo_angle;
                        servo_angle.data.resize(5);
                        servo_angle.data[0] = TICK_TO_RADIAN(servo1_ang);
                        servo_angle.data[1] = TICK_TO_RADIAN(servo2_ang);
                        servo_angle.data[2] = TICK_TO_RADIAN(servo3_ang);
                        servo_angle.data[3] = TICK_TO_RADIAN(servo4_ang);
//			servo_angle.data[4] = TICK_TO_RADIAN(servo5_ang);


                        // 퍼블리시
                        this->_servo_angle_pub->publish(servo_angle);

                };

                timer_ = this->create_wall_timer(10ms, timer_callback);
        }
private:

        rclcpp::TimerBase::SharedPtr timer_;

        rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr _servo_angle_pub;
        rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr _servo_angle_cmd_sub;

};

int main(int argc, char **argv)
{



    std::cout << "Starting dynamixel_fix node..." << std::endl;
    setvbuf(stdout, NULL, _IONBF, BUFSIZ);
    rclcpp::init(argc, argv);
    rclcpp::on_shutdown([]() { KILL_dynamixel(); });
    rclcpp::spin(std::make_shared<DynamixelFix>());
    rclcpp::shutdown();


    return 0;
}

