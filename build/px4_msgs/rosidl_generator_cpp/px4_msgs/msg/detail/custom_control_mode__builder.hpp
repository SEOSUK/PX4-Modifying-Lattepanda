// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/CustomControlMode.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CUSTOM_CONTROL_MODE__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__CUSTOM_CONTROL_MODE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/custom_control_mode__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_CustomControlMode_sine_motion_flag
{
public:
  explicit Init_CustomControlMode_sine_motion_flag(::px4_msgs::msg::CustomControlMode & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::CustomControlMode sine_motion_flag(::px4_msgs::msg::CustomControlMode::_sine_motion_flag_type arg)
  {
    msg_.sine_motion_flag = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::CustomControlMode msg_;
};

class Init_CustomControlMode_custom_mode_flag
{
public:
  explicit Init_CustomControlMode_custom_mode_flag(::px4_msgs::msg::CustomControlMode & msg)
  : msg_(msg)
  {}
  Init_CustomControlMode_sine_motion_flag custom_mode_flag(::px4_msgs::msg::CustomControlMode::_custom_mode_flag_type arg)
  {
    msg_.custom_mode_flag = std::move(arg);
    return Init_CustomControlMode_sine_motion_flag(msg_);
  }

private:
  ::px4_msgs::msg::CustomControlMode msg_;
};

class Init_CustomControlMode_disturbance_observer_flag
{
public:
  explicit Init_CustomControlMode_disturbance_observer_flag(::px4_msgs::msg::CustomControlMode & msg)
  : msg_(msg)
  {}
  Init_CustomControlMode_custom_mode_flag disturbance_observer_flag(::px4_msgs::msg::CustomControlMode::_disturbance_observer_flag_type arg)
  {
    msg_.disturbance_observer_flag = std::move(arg);
    return Init_CustomControlMode_custom_mode_flag(msg_);
  }

private:
  ::px4_msgs::msg::CustomControlMode msg_;
};

class Init_CustomControlMode_timestamp
{
public:
  Init_CustomControlMode_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CustomControlMode_disturbance_observer_flag timestamp(::px4_msgs::msg::CustomControlMode::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_CustomControlMode_disturbance_observer_flag(msg_);
  }

private:
  ::px4_msgs::msg::CustomControlMode msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::CustomControlMode>()
{
  return px4_msgs::msg::builder::Init_CustomControlMode_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__CUSTOM_CONTROL_MODE__BUILDER_HPP_
