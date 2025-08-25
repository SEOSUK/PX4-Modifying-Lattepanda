#include <chrono>
#include <cmath>  
#include <rclcpp/rclcpp.hpp>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

#include <px4_msgs/msg/servo_angle.hpp>
#include <px4_msgs/msg/servo_command.hpp>
#include <px4_msgs/msg/wrench_command.hpp>
#include <px4_msgs/msg/thrust_command.hpp>
#include <px4_msgs/msg/actuator_servos.hpp>
#include <px4_msgs/msg/vehicle_torque_non_norm.hpp>
#include <px4_msgs/msg/vehicle_thrust_non_norm.hpp>
#include <px4_msgs/msg/vehicle_acceleration.hpp>

#include <px4_msgs/msg/vehicle_torque_setpoint.hpp>
#include <px4_msgs/msg/vehicle_thrust_setpoint.hpp>
#include <px4_msgs/msg/vehicle_odometry.hpp>
#include <px4_msgs/msg/vehicle_local_position_setpoint.hpp>
#include <px4_msgs/msg/vehicle_local_position.hpp>
#include <px4_msgs/msg/actuator_motors.hpp>

#include <px4_msgs/msg/custom_control_mode.hpp>
#include <px4_msgs/msg/center_of_mass.hpp>
#include <px4_msgs/msg/torque_dhat.hpp>

#include "std_msgs/msg/float32_multi_array.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"


using namespace std::chrono_literals;

std::chrono::duration<float> delta_t;

//Timer------------------------------------------------
auto end  =std::chrono::high_resolution_clock::now();
auto start=std::chrono::high_resolution_clock::now();


// ===== 2nd-order Butterworth LPF (DF2T) =====
struct Biquad {
    float b0{0.f}, b1{0.f}, b2{0.f}, a1{0.f}, a2{0.f};
    float s1{0.f}, s2{0.f};

    inline void setButter2Lowpass(float fc_Hz, float fs_Hz) {
        // bilinear transform, pre-warp
        const float PI_F = 3.14159265358979323846f;
        const float K = tanf(PI_F * fc_Hz / fs_Hz);   // pre-warped
        const float KK = K * K;
        const float denom_inv = 1.f / (1.f + 1.41421356f * K + KK); // sqrt(2)=1.4142..

        b0 = KK * denom_inv;
        b1 = 2.f * b0;
        b2 = b0;
        a1 = 2.f * (KK - 1.f) * denom_inv;
        a2 = (1.f - 1.41421356f * K + KK) * denom_inv;

        // reset states
        s1 = 0.f; s2 = 0.f;
    }

    inline float step(float x) {
        // Direct Form II Transposed
        const float y = b0 * x + s1;
        s1 = b1 * x - a1 * y + s2;
        s2 = b2 * x - a2 * y;
        return y;
    }
};


class ListenAndSpeakRos : public rclcpp::Node
{
public:
        ListenAndSpeakRos() : Node("ListenAndSpeakRos")
        {

		
		// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
                // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡQOS SETTINGㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
                // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //

                rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
                auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 6), qos_profile);


		// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
                // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡPUBLISHERㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
                // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //

		custom_control_mode_pub = this->create_publisher<px4_msgs::msg::CustomControlMode>("/fmu/in/custom_control_mode", 1);

		servo_angle_px4_pub = this->create_publisher<px4_msgs::msg::ServoAngle>("/fmu/in/servo_angle", 10);
		servo_angle_cmd_pub = this->create_publisher<std_msgs::msg::Float32MultiArray>("servo_angle_cmd", 1);

		torque_command_pub  = this->create_publisher<std_msgs::msg::Float32MultiArray>("torque_cmd", 1);
		force_command_pub  = this->create_publisher<std_msgs::msg::Float32MultiArray>("force_cmd", 1);
		thrust_command_pub  = this->create_publisher<std_msgs::msg::Float32MultiArray>("thrust_cmd", 1);

		data_logging_pub = this->create_publisher<std_msgs::msg::Float32MultiArray>("data_logging_msg", qos);


		// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
		// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡSUBSCRIBERㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
		// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //

                torque_command_sub = this->create_subscription<px4_msgs::msg::VehicleTorqueSetpoint>("/fmu/out/vehicle_torque_setpoint", qos,
                [this](const px4_msgs::msg::VehicleTorqueSetpoint::UniquePtr msg) {
			
			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			tx = msg->xyz[0];
			ty = msg->xyz[1];
    			tz = msg->xyz[2];
			tz_trim = msg->yaw_trim;


                });

		force_command_sub = this->create_subscription<px4_msgs::msg::VehicleThrustSetpoint>("/fmu/out/vehicle_thrust_setpoint", qos,
                [this](const px4_msgs::msg::VehicleThrustSetpoint::UniquePtr msg) {

                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			fx = msg->xyz[0];
    			fy = msg->xyz[1];
			fz = msg->xyz[2];
                });

		wrench_command_sub = this->create_subscription<px4_msgs::msg::WrenchCommand>("/fmu/out/wrench_command", qos,
                [this](const px4_msgs::msg::WrenchCommand::UniquePtr msg) {

                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
                        /*
			fx = msg->fx_d;
                        fy = msg->fy_d;
                        fz = msg->fz_d;

			tx = msg->tr_d;
			ty = msg->tp_d;
			tz = msg->ty_d; */
                });

		thrust_command_sub = this->create_subscription<px4_msgs::msg::ThrustCommand>("/fmu/out/thrust_command", qos,
                [this](const px4_msgs::msg::ThrustCommand::UniquePtr msg) {
                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			
			f1 = setThrustLimitation(msg->thrust_command[0]);
			f2 = setThrustLimitation(msg->thrust_command[1]);
			f3 = setThrustLimitation(msg->thrust_command[2]);
			f4 = setThrustLimitation(msg->thrust_command[3]);
                });

		motor_command_sub = this->create_subscription<px4_msgs::msg::ActuatorMotors>("/fmu/out/actuator_motors", qos,
                [this](const px4_msgs::msg::ActuatorMotors::UniquePtr msg) {
                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
                        
                        pwm1 = msg->control[0];
                        pwm2 = msg->control[1];
                        pwm3 = msg->control[2];
                        pwm4 = msg->control[3];
                        

                });


		vehicle_odometry_sub = this->create_subscription<px4_msgs::msg::VehicleOdometry>("/fmu/out/vehicle_odometry", qos,
				
                [this](const px4_msgs::msg::VehicleOdometry::UniquePtr msg) {
                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			
		
			px = msg->position[0];
			py = msg->position[1];
			pz = msg->position[2];

			vx = msg->velocity[0];
			vy = msg->velocity[1];
			vz = msg->velocity[2];

			//ax = msg->ax;
			//ay = msg->ay;
			//az = msg->az;
			
			qw = msg->q[0];
			qx = msg->q[1];
			qy = msg->q[2];
			qz = msg->q[3];
			
			Eigen::Quaternionf qf(qw, qx, qy, qz);
			Eigen::Quaterniond q = qf.cast<double>();
                        Eigen::Matrix3d R = q.toRotationMatrix();
			//Eigen::Vector3d euler = R.eulerAngles(2,1,0);
			
			double roll  = std::atan2(R(2,1), R(2,2));
			double pitch = std::asin(-R(2,0));
			double yaw   = std::atan2(R(1,0), R(0,0));

			rx = static_cast<float>(roll);//euler[2]
			ry = static_cast<float>(pitch);//euler[1]
			rz = static_cast<float>(yaw);//euler[0]

			rxd = msg->angular_velocity[0];
			ryd = msg->angular_velocity[1];
			rzd = msg->angular_velocity[2];

                });


		vehicle_local_position_setpoint_sub = this->create_subscription<px4_msgs::msg::VehicleLocalPositionSetpoint>("/fmu/out/vehicle_local_position_setpoint", qos,
                [this](const px4_msgs::msg::VehicleLocalPositionSetpoint::UniquePtr msg) {

                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			
		 	px_d = msg->x;
			py_d = msg->y;
			pz_d = msg->z;

			vx_d = msg->vx;
			vy_d = msg->vy;
			vz_d = msg->vz;

			ax_d = msg->acceleration[0];
			ay_d = msg->acceleration[1];
			az_d = msg->acceleration[2];

			rx_d = 0.f;
			ry_d = 0.f;
			rz_d = msg->yaw;

                });

		vehicle_acceleration_sub = this->create_subscription<px4_msgs::msg::VehicleAcceleration>("/fmu/out/vehicle_acceleration", qos,
                [this](const px4_msgs::msg::VehicleAcceleration::UniquePtr msg) {

                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //

                        ax = msg->xyz[0];
                        ay = msg->xyz[1];
                        az = msg->xyz[2];

                });

		servo_angle_ros2_sub = this->create_subscription<std_msgs::msg::Float32MultiArray>("servo_angle", qos,
                [this](const std_msgs::msg::Float32MultiArray::UniquePtr msg) {
                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //

			th1_act = msg->data[0];
			th2_act = msg->data[1];
			th3_act = msg->data[2];
			th4_act = msg->data[3];
			th5_act = msg->data[4];
                });

		center_of_mass_sub = this->create_subscription<px4_msgs::msg::CenterOfMass>("/fmu/out/center_of_mass", qos,
                [this](const px4_msgs::msg::CenterOfMass::UniquePtr msg) {

			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			present_com_x = msg->present_com_hat[0]; 
		       	present_com_y = msg->present_com_hat[1];
		       	present_com_z = msg->present_com_hat[2]; 
			
			past_com_x = msg->past_com_hat[0];
		       	past_com_y = msg->past_com_hat[1];
		       	past_com_z = msg->past_com_hat[2];
			
			com_tilde_x = msg->com_tilde[0]; 
			com_tilde_y = msg->com_tilde[1]; 
			com_tilde_z = msg->com_tilde[2];
			
			com_update_x = msg->com_update[0];
			com_update_y = msg->com_update[1];  
			com_update_z = msg->com_update[2];


		});

		torque_dhat_sub = this->create_subscription<px4_msgs::msg::TorqueDhat>("/fmu/out/torque_dhat", qos,
                [this](const px4_msgs::msg::TorqueDhat::UniquePtr msg) {

                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
                        tx_dhat = msg->xyz[0];
                        ty_dhat = msg->xyz[1];
                        tz_dhat = msg->xyz[2];

                });

		custom_control_mode_sub = this->create_subscription<std_msgs::msg::Int32MultiArray>("control_mode_flags", qos,
                [this](const std_msgs::msg::Int32MultiArray::UniquePtr msg) {
                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
                        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			dob_flag = sanitize_int(msg->data[0]);
			custom_mode_flag = sanitize_int(msg->data[1]);

			
		});

		

		// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
		// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ TIMER CALLBACK LOOP ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
		// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
		// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
		
			
		auto timer_callback = [this]()->void {


			//std::cout << " Timer callback running!" << std::endl;
			
			Eigen::Matrix4f SA;
	                Eigen::Matrix4f invSA;
        	        Eigen::Vector4f wrench_servo(fx, fy, tz_trim, 0.0);
			// Eigen::Vector4f wrench_servo(fx, fy, 0.0, 0.0);
			// fz의 부호와 thrust_command의 부호가 같아야함 즉 양수여야함
	
        	        float r_arm = 0.21;
           	    	float r2 = sqrt(2);

             		SA <<  f1/r2,     f2/r2,     -(f3/r2),     -(f4/r2),
                        	f1/r2,    -(f2/r2),   -(f3/r2),       f4/r2,
                        	r_arm*f1,  r_arm*f2,   r_arm*f3,   r_arm*f4,
                        	r_arm*f1, -(r_arm*f2),   r_arm*f3,  -(r_arm*f4);
			if (SA.determinant() != 0) {
	                invSA=SA.inverse();

        	        Eigen::Vector4f sine_theta_command = invSA*wrench_servo;

                	th1_cmd = asin(asine_safety(sine_theta_command(0)));
	                th2_cmd = asin(asine_safety(sine_theta_command(1)));
	                th3_cmd = asin(asine_safety(sine_theta_command(2)));
	                th4_cmd = asin(asine_safety(sine_theta_command(3)));
			}
			if(th1_cmd < 0.001 && th1_cmd > -0.001){th1_cmd = 0.0;}
			if(th2_cmd < 0.001 && th2_cmd > -0.001){th2_cmd = 0.0;}
			if(th3_cmd < 0.001 && th3_cmd > -0.001){th3_cmd = 0.0;}
			if(th4_cmd < 0.001 && th4_cmd > -0.001){th4_cmd = 0.0;}

			std_msgs::msg::Float32MultiArray servo_angle_command;
		        servo_angle_command.data.resize(5);
        		servo_angle_command.data[0] = th1_cmd;
		        servo_angle_command.data[1] = th2_cmd;
		        servo_angle_command.data[2] = th3_cmd;
		        servo_angle_command.data[3] = th4_cmd;
			servo_angle_command.data[4] = tray_angle_command;

			// 퍼블리시
                        this->servo_angle_cmd_pub->publish(servo_angle_command);

			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			
			
			std_msgs::msg::Float32MultiArray torque_command;
                        torque_command.data.resize(3);
                        torque_command.data[0] = tx;
                        torque_command.data[1] = ty;
                        torque_command.data[2] = tz;

                        // 퍼블리시
                        this->torque_command_pub->publish(torque_command);
			
			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			
			std_msgs::msg::Float32MultiArray force_command;
                        force_command.data.resize(3);
                        force_command.data[0] = fx;
                        force_command.data[1] = fy;
                        force_command.data[2] = fz;

                        // 퍼블리시
                        this->force_command_pub->publish(force_command);

			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			

			std_msgs::msg::Float32MultiArray thrust_command;
                        thrust_command.data.resize(4);
                        thrust_command.data[0] = f1;
                        thrust_command.data[1] = f2;
                        thrust_command.data[2] = f3;
                        thrust_command.data[3] = f4;

                        // 퍼블리시
                        this->thrust_command_pub->publish(thrust_command);
			
			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			/*	
			std::cout << "============================="   << std::endl;
                        std::cout << "tx: " << tx   << std::endl;
                        std::cout << "ty: " << ty  << std::endl;
                        std::cout << "zz: " << tz  << std::endl;*/
                        //std::cout << "f4: " << msg->gyro_rad[2]  << std::endl;
			
			
			auto servo_angle_msg = px4_msgs::msg::ServoAngle();
                        servo_angle_msg.timestamp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()).time_since_epoch().count();
                        std::string name = "servo_angle";


			if(th1_act < 0.001 && th1_act > -0.001){th1_act = 0.0;}
                	if(th2_act < 0.001 && th2_act > -0.001){th2_act = 0.0;}
               	 	if(th3_act < 0.001 && th3_act > -0.001){th3_act = 0.0;}
                	if(th4_act < 0.001 && th4_act > -0.001){th4_act = 0.0;}

			servo_angle_msg.servo_angle[0] = th1_act;
			servo_angle_msg.servo_angle[1] = th2_act;
			servo_angle_msg.servo_angle[2] = th3_act;
			servo_angle_msg.servo_angle[3] = th4_act;

                        this->servo_angle_px4_pub->publish(servo_angle_msg);

			
			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //	

			auto control_mode_msg = px4_msgs::msg::CustomControlMode();
                        control_mode_msg.timestamp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::steady_clock::now()).time_since_epoch().count();

			control_mode_msg.disturbance_observer_flag = dob_flag;
			control_mode_msg.custom_mode_flag = custom_mode_flag;

			this->custom_control_mode_pub->publish(control_mode_msg);


			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡFOR DATA LOGGINGㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
			
			std::vector<float> raw_data = {
				px, py, pz,
			    	px_d, py_d, pz_d,
			    	vx, vy, vz,
			    	vx_d, vy_d, vz_d,
			    	rx, ry, rz,
			    	rx_d, ry_d, rz_d,
			    	rxd, ryd, rzd,
			    	rxd_d, ryd_d, rzd_d,
			    	fx, fy, fz,
			    	tx, ty, tz, 
				tz_trim,
				tx_dhat, ty_dhat, tz_dhat,
			    	f1, f2, f3, f4,
			    	th1_act, th2_act, th3_act, th4_act, th5_act,
			    	th1_cmd, th2_cmd, th3_cmd, th4_cmd, tray_angle_command,
				ax, ay, az,
				ax_d, ay_d, az_d,
				present_com_x, present_com_y, present_com_z,
				past_com_x, past_com_y, past_com_z,
				com_tilde_x, com_tilde_y, com_tilde_z,
				com_update_x, com_update_y,com_update_z
				
			};

			// 메시지 생성 및 초기화
			std_msgs::msg::Float32MultiArray data_log_array;
			data_log_array.data.resize(raw_data.size());
			// sanitize 후 저장
			for (size_t i = 0; i < raw_data.size(); ++i) {
				data_log_array.data[i] = sanitize(raw_data[i]);
			}
			

                        // 퍼블리시
                        this->data_logging_pub->publish(data_log_array);


                };

                timer_ = this->create_wall_timer(12ms, timer_callback);



        }

private:

	// --- Servo command LPF (for th1..th4) ---
	Biquad lpf_th_[4];
	bool   lpf_inited_{false};
	rclcpp::Time lpf_prev_time_;  // dt 계산용 (초기 0)

	float fx = 0.0f, fy = 0.0f, fz = 0.0f, tx = 0.0f, ty = 0.0f, tz = 0.0f, tz_trim = 0.0f;
	float tx_dhat = 0.f, ty_dhat = 0.f, tz_dhat = 0.f;
	float f1 = 0.0f, f2 = 0.0f, f3 = 0.0f, f4 = 0.0f;
	float pwm1 = 0.0f, pwm2 = 0.0f, pwm3 = 0.0f, pwm4 = 0.0f;
	float th1_cmd = 0.0f, th2_cmd = 0.0f, th3_cmd = 0.0f, th4_cmd = 0.0f, th5_cmd;
	float th1_act = 0.0f, th2_act = 0.0f, th3_act = 0.0f, th4_act = 0.0f, th5_act;

	float px = 0.f, py = 0.f, pz = 0.f, qx = 0.f, qy = 0.f, qz = 0.f, qw = 0.f;
	float vx = 0.f, vy = 0.f, vz = 0.f, rx = 0.f, ry = 0.f, rz = 0.f;
	float ax = 0.f, ay = 0.f, az = 0.f, rxd = 0.f, ryd = 0.f, rzd = 0.f;
	float px_d = 0.f, py_d = 0.f, pz_d = 0.f, rx_d = 0.f, ry_d = 0.f, rz_d = 0.f;
	float vx_d = 0.f, vy_d = 0.f, vz_d = 0.f, rxd_d = 0.f, ryd_d = 0.f, rzd_d = 0.f;
	float ax_d = 0.f, ay_d = 0.f, az_d = 0.f; 

	float present_com_x = 0.f, present_com_y = 0.f, present_com_z = 0.f;
	float past_com_x = 0.f, past_com_y = 0.f, past_com_z = 0.f;
	float com_tilde_x = 0.f, com_tilde_y = 0.f, com_tilde_z = 0.f;
	float com_update_x = 0.f, com_update_y = 0.f, com_update_z = 0.f;

	

	

	int dob_flag = 0; int custom_mode_flag = 0; 
	

	int radian_count_ = 0;
	int count_ = 0;
	int direction_ = 1; // 1이면 시계 방향, -1이면 반시계 방향
	float radian_command = 0.174533;
	float tray_angle_command = 0.f;
	// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ  Utility Function ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
        // ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //

	double wrapToPi(double angle) {
		return std::atan2(std::sin(angle), std::cos(angle));
	}		

	inline int sanitize_int(int value) {
		return std::isnan(value) ? 0 : value;
	}

	inline float sanitize(float value) {
		return std::isnan(value) ? 0.f : value;
	}

        float asine_safety(float x) {
		if (x > 0.3f) return 0.3f;
                if (x < -0.3f) return -0.3f;
		return x;
	}

	float setThrustLimitation(float thrust_command){
                        if(thrust_command < 2.0){ thrust_command = 2.0;}
                        if(thrust_command > 55.0){ thrust_command = 55.0;}
                        return thrust_command;
	}

	// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
        
	rclcpp::TimerBase::SharedPtr timer_;

	rclcpp::Time t_prev_;  
	
	// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
	
        rclcpp::Publisher<px4_msgs::msg::ServoAngle>::SharedPtr servo_angle_px4_pub;
	rclcpp::Publisher<px4_msgs::msg::CustomControlMode>::SharedPtr custom_control_mode_pub;
	rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr servo_angle_cmd_pub;

	rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr torque_command_pub;
	rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr force_command_pub;
	rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr thrust_command_pub;


	rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr data_logging_pub;
	
	// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
	
	rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr custom_control_mode_sub;
	rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr servo_angle_ros2_sub;
	rclcpp::Subscription<px4_msgs::msg::VehicleTorqueSetpoint>::SharedPtr torque_command_sub;
	rclcpp::Subscription<px4_msgs::msg::ThrustCommand>::SharedPtr thrust_command_sub;
	rclcpp::Subscription<px4_msgs::msg::WrenchCommand>::SharedPtr wrench_command_sub;
	rclcpp::Subscription<px4_msgs::msg::ActuatorMotors>::SharedPtr motor_command_sub;
 	rclcpp::Subscription<px4_msgs::msg::VehicleThrustSetpoint>::SharedPtr force_command_sub;

	rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr vehicle_odometry_sub;
	rclcpp::Subscription<px4_msgs::msg::VehicleLocalPositionSetpoint>::SharedPtr vehicle_local_position_setpoint_sub;

	rclcpp::Subscription<px4_msgs::msg::VehicleAcceleration>::SharedPtr vehicle_acceleration_sub;
	rclcpp::Subscription<px4_msgs::msg::CenterOfMass>::SharedPtr center_of_mass_sub;

	rclcpp::Subscription<px4_msgs::msg::TorqueDhat>::SharedPtr torque_dhat_sub;
	

};

int main(int argc, char *argv[])
{

	// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //
	
	// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ //

        std::cout << "Starting servo_angle_msg advertiser node..." << std::endl;
        setvbuf(stdout, NULL, _IONBF, BUFSIZ);
        rclcpp::init(argc, argv);
        rclcpp::spin(std::make_shared<ListenAndSpeakRos>());

        rclcpp::shutdown();
        return 0;
}
