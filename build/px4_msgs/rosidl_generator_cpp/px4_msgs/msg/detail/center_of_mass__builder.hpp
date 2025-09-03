// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/CenterOfMass.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/center_of_mass__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_CenterOfMass_com_update
{
public:
  explicit Init_CenterOfMass_com_update(::px4_msgs::msg::CenterOfMass & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::CenterOfMass com_update(::px4_msgs::msg::CenterOfMass::_com_update_type arg)
  {
    msg_.com_update = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::CenterOfMass msg_;
};

class Init_CenterOfMass_com_tilde
{
public:
  explicit Init_CenterOfMass_com_tilde(::px4_msgs::msg::CenterOfMass & msg)
  : msg_(msg)
  {}
  Init_CenterOfMass_com_update com_tilde(::px4_msgs::msg::CenterOfMass::_com_tilde_type arg)
  {
    msg_.com_tilde = std::move(arg);
    return Init_CenterOfMass_com_update(msg_);
  }

private:
  ::px4_msgs::msg::CenterOfMass msg_;
};

class Init_CenterOfMass_past_com_hat
{
public:
  explicit Init_CenterOfMass_past_com_hat(::px4_msgs::msg::CenterOfMass & msg)
  : msg_(msg)
  {}
  Init_CenterOfMass_com_tilde past_com_hat(::px4_msgs::msg::CenterOfMass::_past_com_hat_type arg)
  {
    msg_.past_com_hat = std::move(arg);
    return Init_CenterOfMass_com_tilde(msg_);
  }

private:
  ::px4_msgs::msg::CenterOfMass msg_;
};

class Init_CenterOfMass_present_com_hat
{
public:
  explicit Init_CenterOfMass_present_com_hat(::px4_msgs::msg::CenterOfMass & msg)
  : msg_(msg)
  {}
  Init_CenterOfMass_past_com_hat present_com_hat(::px4_msgs::msg::CenterOfMass::_present_com_hat_type arg)
  {
    msg_.present_com_hat = std::move(arg);
    return Init_CenterOfMass_past_com_hat(msg_);
  }

private:
  ::px4_msgs::msg::CenterOfMass msg_;
};

class Init_CenterOfMass_timestamp
{
public:
  Init_CenterOfMass_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CenterOfMass_present_com_hat timestamp(::px4_msgs::msg::CenterOfMass::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_CenterOfMass_present_com_hat(msg_);
  }

private:
  ::px4_msgs::msg::CenterOfMass msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::CenterOfMass>()
{
  return px4_msgs::msg::builder::Init_CenterOfMass_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__BUILDER_HPP_
