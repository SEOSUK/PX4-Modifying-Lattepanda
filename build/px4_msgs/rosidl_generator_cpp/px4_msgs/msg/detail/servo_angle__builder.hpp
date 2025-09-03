// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/ServoAngle.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__SERVO_ANGLE__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__SERVO_ANGLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/servo_angle__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_ServoAngle_servo_angle
{
public:
  explicit Init_ServoAngle_servo_angle(::px4_msgs::msg::ServoAngle & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::ServoAngle servo_angle(::px4_msgs::msg::ServoAngle::_servo_angle_type arg)
  {
    msg_.servo_angle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::ServoAngle msg_;
};

class Init_ServoAngle_timestamp
{
public:
  Init_ServoAngle_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoAngle_servo_angle timestamp(::px4_msgs::msg::ServoAngle::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_ServoAngle_servo_angle(msg_);
  }

private:
  ::px4_msgs::msg::ServoAngle msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::ServoAngle>()
{
  return px4_msgs::msg::builder::Init_ServoAngle_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__SERVO_ANGLE__BUILDER_HPP_
