// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/TorqueDhat.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__TORQUE_DHAT__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__TORQUE_DHAT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/torque_dhat__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_TorqueDhat_xyz
{
public:
  explicit Init_TorqueDhat_xyz(::px4_msgs::msg::TorqueDhat & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::TorqueDhat xyz(::px4_msgs::msg::TorqueDhat::_xyz_type arg)
  {
    msg_.xyz = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::TorqueDhat msg_;
};

class Init_TorqueDhat_timestamp
{
public:
  Init_TorqueDhat_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TorqueDhat_xyz timestamp(::px4_msgs::msg::TorqueDhat::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_TorqueDhat_xyz(msg_);
  }

private:
  ::px4_msgs::msg::TorqueDhat msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::TorqueDhat>()
{
  return px4_msgs::msg::builder::Init_TorqueDhat_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__TORQUE_DHAT__BUILDER_HPP_
