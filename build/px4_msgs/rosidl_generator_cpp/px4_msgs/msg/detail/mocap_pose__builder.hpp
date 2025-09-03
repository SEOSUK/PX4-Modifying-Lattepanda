// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/MocapPose.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__MOCAP_POSE__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__MOCAP_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/mocap_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_MocapPose_rw
{
public:
  explicit Init_MocapPose_rw(::px4_msgs::msg::MocapPose & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::MocapPose rw(::px4_msgs::msg::MocapPose::_rw_type arg)
  {
    msg_.rw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::MocapPose msg_;
};

class Init_MocapPose_rz
{
public:
  explicit Init_MocapPose_rz(::px4_msgs::msg::MocapPose & msg)
  : msg_(msg)
  {}
  Init_MocapPose_rw rz(::px4_msgs::msg::MocapPose::_rz_type arg)
  {
    msg_.rz = std::move(arg);
    return Init_MocapPose_rw(msg_);
  }

private:
  ::px4_msgs::msg::MocapPose msg_;
};

class Init_MocapPose_ry
{
public:
  explicit Init_MocapPose_ry(::px4_msgs::msg::MocapPose & msg)
  : msg_(msg)
  {}
  Init_MocapPose_rz ry(::px4_msgs::msg::MocapPose::_ry_type arg)
  {
    msg_.ry = std::move(arg);
    return Init_MocapPose_rz(msg_);
  }

private:
  ::px4_msgs::msg::MocapPose msg_;
};

class Init_MocapPose_rx
{
public:
  explicit Init_MocapPose_rx(::px4_msgs::msg::MocapPose & msg)
  : msg_(msg)
  {}
  Init_MocapPose_ry rx(::px4_msgs::msg::MocapPose::_rx_type arg)
  {
    msg_.rx = std::move(arg);
    return Init_MocapPose_ry(msg_);
  }

private:
  ::px4_msgs::msg::MocapPose msg_;
};

class Init_MocapPose_z
{
public:
  explicit Init_MocapPose_z(::px4_msgs::msg::MocapPose & msg)
  : msg_(msg)
  {}
  Init_MocapPose_rx z(::px4_msgs::msg::MocapPose::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_MocapPose_rx(msg_);
  }

private:
  ::px4_msgs::msg::MocapPose msg_;
};

class Init_MocapPose_y
{
public:
  explicit Init_MocapPose_y(::px4_msgs::msg::MocapPose & msg)
  : msg_(msg)
  {}
  Init_MocapPose_z y(::px4_msgs::msg::MocapPose::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_MocapPose_z(msg_);
  }

private:
  ::px4_msgs::msg::MocapPose msg_;
};

class Init_MocapPose_x
{
public:
  explicit Init_MocapPose_x(::px4_msgs::msg::MocapPose & msg)
  : msg_(msg)
  {}
  Init_MocapPose_y x(::px4_msgs::msg::MocapPose::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_MocapPose_y(msg_);
  }

private:
  ::px4_msgs::msg::MocapPose msg_;
};

class Init_MocapPose_timestamp
{
public:
  Init_MocapPose_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MocapPose_x timestamp(::px4_msgs::msg::MocapPose::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_MocapPose_x(msg_);
  }

private:
  ::px4_msgs::msg::MocapPose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::MocapPose>()
{
  return px4_msgs::msg::builder::Init_MocapPose_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__MOCAP_POSE__BUILDER_HPP_
