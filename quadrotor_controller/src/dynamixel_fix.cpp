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


#define ADDR_POSITION_D_GAIN 80
#define ADDR_POSITION_I_GAIN 82
#define ADDR_POSITION_P_GAIN 84


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
float payload_angle_cmd = 0.f;
uint32_t servo1_ang = 0;
uint32_t servo2_ang = 0;
uint32_t servo3_ang = 0;
uint32_t servo4_ang = 0;
uint32_t servo5_ang = 0;
float amplitude = 0.5;
//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //

void SET_SERVO5_POSITION_PID(uint16_t p, uint16_t i, uint16_t d)
{
    // Torque ON 상태에서도 쓰기 되는 모델이 있지만,
    // 안전하게 하려면 torque off -> write -> torque on 권장.
    packetHandler->write1ByteTxRx(portHandler, 5, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);

    packetHandler->write2ByteTxRx(portHandler, 5, ADDR_POSITION_D_GAIN, d, nullptr);
    packetHandler->write2ByteTxRx(portHandler, 5, ADDR_POSITION_I_GAIN, i, nullptr);
    packetHandler->write2ByteTxRx(portHandler, 5, ADDR_POSITION_P_GAIN, p, nullptr);

    packetHandler->write1ByteTxRx(portHandler, 5, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, nullptr);
}


void CONNECT_dynamixel()
{
    portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    portHandler->openPort();
    portHandler->setBaudRate(BAUDRATE);
}

void READ_SERVO5_POSITION_PID()
{
    uint16_t p=0,i=0,d=0;
    packetHandler->read2ByteTxRx(portHandler, 5, ADDR_POSITION_P_GAIN, &p, nullptr);
    packetHandler->read2ByteTxRx(portHandler, 5, ADDR_POSITION_I_GAIN, &i, nullptr);
    packetHandler->read2ByteTxRx(portHandler, 5, ADDR_POSITION_D_GAIN, &d, nullptr);

    std::cout << "[ID5 PID] P=" << p << " I=" << i << " D=" << d << std::endl;
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

    packetHandler->write1ByteTxRx(portHandler, 5, ADDR_OPERATING_MODE, 3, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 5, ADDR_TORQUE_ENABLE, TORQUE_ENABLE, nullptr);

        SET_SERVO5_POSITION_PID(/*P*/ 2000, /*I*/ 200, /*D*/ 600);
        READ_SERVO5_POSITION_PID();
}

void KILL_dynamixel()
{
    packetHandler->write1ByteTxRx(portHandler, 1, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 2, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 3, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 4, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);
    packetHandler->write1ByteTxRx(portHandler, 5, ADDR_TORQUE_ENABLE, TORQUE_DISABLE, nullptr);


    portHandler->closePort();
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
  packetHandler->write4ByteTxRx(portHandler, 5, ADDR_GOAL_POSITION, RADIAN_TO_TICK(payload_angle_cmd), nullptr);

  // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //


  packetHandler->read4ByteTxRx(portHandler,1,ADDR_PRESENT_POSITION,&servo1_ang,nullptr);
  packetHandler->read4ByteTxRx(portHandler,2,ADDR_PRESENT_POSITION,&servo2_ang,nullptr);
  packetHandler->read4ByteTxRx(portHandler,3,ADDR_PRESENT_POSITION,&servo3_ang,nullptr);
  packetHandler->read4ByteTxRx(portHandler,4,ADDR_PRESENT_POSITION,&servo4_ang,nullptr);
  packetHandler->read4ByteTxRx(portHandler,5,ADDR_PRESENT_POSITION,&servo5_ang,nullptr);

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
			payload_angle_cmd = msg->data[4];


                });



                auto timer_callback = [this]()->void {

                        READWRITE_dynamixel();


                        std_msgs::msg::Float32MultiArray servo_angle;
                        servo_angle.data.resize(5);
                        servo_angle.data[0] = TICK_TO_RADIAN(servo1_ang);
                        servo_angle.data[1] = TICK_TO_RADIAN(servo2_ang);
                        servo_angle.data[2] = TICK_TO_RADIAN(servo3_ang);
                        servo_angle.data[3] = TICK_TO_RADIAN(servo4_ang);
			servo_angle.data[4] = TICK_TO_RADIAN(servo5_ang);


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

