// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/VehicleMocapOdometry.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_MOCAP_ODOMETRY__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_MOCAP_ODOMETRY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/vehicle_mocap_odometry__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleMocapOdometry_quality_flag
{
public:
  explicit Init_VehicleMocapOdometry_quality_flag(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::VehicleMocapOdometry quality_flag(::px4_msgs::msg::VehicleMocapOdometry::_quality_flag_type arg)
  {
    msg_.quality_flag = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_reset_counter
{
public:
  explicit Init_VehicleMocapOdometry_reset_counter(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_quality_flag reset_counter(::px4_msgs::msg::VehicleMocapOdometry::_reset_counter_type arg)
  {
    msg_.reset_counter = std::move(arg);
    return Init_VehicleMocapOdometry_quality_flag(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_angular_velocity_variance
{
public:
  explicit Init_VehicleMocapOdometry_angular_velocity_variance(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_reset_counter angular_velocity_variance(::px4_msgs::msg::VehicleMocapOdometry::_angular_velocity_variance_type arg)
  {
    msg_.angular_velocity_variance = std::move(arg);
    return Init_VehicleMocapOdometry_reset_counter(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_velocity_variance
{
public:
  explicit Init_VehicleMocapOdometry_velocity_variance(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_angular_velocity_variance velocity_variance(::px4_msgs::msg::VehicleMocapOdometry::_velocity_variance_type arg)
  {
    msg_.velocity_variance = std::move(arg);
    return Init_VehicleMocapOdometry_angular_velocity_variance(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_orientation_variance
{
public:
  explicit Init_VehicleMocapOdometry_orientation_variance(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_velocity_variance orientation_variance(::px4_msgs::msg::VehicleMocapOdometry::_orientation_variance_type arg)
  {
    msg_.orientation_variance = std::move(arg);
    return Init_VehicleMocapOdometry_velocity_variance(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_position_variance
{
public:
  explicit Init_VehicleMocapOdometry_position_variance(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_orientation_variance position_variance(::px4_msgs::msg::VehicleMocapOdometry::_position_variance_type arg)
  {
    msg_.position_variance = std::move(arg);
    return Init_VehicleMocapOdometry_orientation_variance(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_angular_velocity
{
public:
  explicit Init_VehicleMocapOdometry_angular_velocity(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_position_variance angular_velocity(::px4_msgs::msg::VehicleMocapOdometry::_angular_velocity_type arg)
  {
    msg_.angular_velocity = std::move(arg);
    return Init_VehicleMocapOdometry_position_variance(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_velocity
{
public:
  explicit Init_VehicleMocapOdometry_velocity(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_angular_velocity velocity(::px4_msgs::msg::VehicleMocapOdometry::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_VehicleMocapOdometry_angular_velocity(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_q
{
public:
  explicit Init_VehicleMocapOdometry_q(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_velocity q(::px4_msgs::msg::VehicleMocapOdometry::_q_type arg)
  {
    msg_.q = std::move(arg);
    return Init_VehicleMocapOdometry_velocity(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_position
{
public:
  explicit Init_VehicleMocapOdometry_position(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_q position(::px4_msgs::msg::VehicleMocapOdometry::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_VehicleMocapOdometry_q(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_pose_frame
{
public:
  explicit Init_VehicleMocapOdometry_pose_frame(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_position pose_frame(::px4_msgs::msg::VehicleMocapOdometry::_pose_frame_type arg)
  {
    msg_.pose_frame = std::move(arg);
    return Init_VehicleMocapOdometry_position(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_timestamp_sample
{
public:
  explicit Init_VehicleMocapOdometry_timestamp_sample(::px4_msgs::msg::VehicleMocapOdometry & msg)
  : msg_(msg)
  {}
  Init_VehicleMocapOdometry_pose_frame timestamp_sample(::px4_msgs::msg::VehicleMocapOdometry::_timestamp_sample_type arg)
  {
    msg_.timestamp_sample = std::move(arg);
    return Init_VehicleMocapOdometry_pose_frame(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

class Init_VehicleMocapOdometry_timestamp
{
public:
  Init_VehicleMocapOdometry_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleMocapOdometry_timestamp_sample timestamp(::px4_msgs::msg::VehicleMocapOdometry::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_VehicleMocapOdometry_timestamp_sample(msg_);
  }

private:
  ::px4_msgs::msg::VehicleMocapOdometry msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::VehicleMocapOdometry>()
{
  return px4_msgs::msg::builder::Init_VehicleMocapOdometry_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_MOCAP_ODOMETRY__BUILDER_HPP_
