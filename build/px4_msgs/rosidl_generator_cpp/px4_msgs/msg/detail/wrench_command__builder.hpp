// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from px4_msgs:msg/WrenchCommand.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__BUILDER_HPP_
#define PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "px4_msgs/msg/detail/wrench_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace px4_msgs
{

namespace msg
{

namespace builder
{

class Init_WrenchCommand_ty_d
{
public:
  explicit Init_WrenchCommand_ty_d(::px4_msgs::msg::WrenchCommand & msg)
  : msg_(msg)
  {}
  ::px4_msgs::msg::WrenchCommand ty_d(::px4_msgs::msg::WrenchCommand::_ty_d_type arg)
  {
    msg_.ty_d = std::move(arg);
    return std::move(msg_);
  }

private:
  ::px4_msgs::msg::WrenchCommand msg_;
};

class Init_WrenchCommand_tp_d
{
public:
  explicit Init_WrenchCommand_tp_d(::px4_msgs::msg::WrenchCommand & msg)
  : msg_(msg)
  {}
  Init_WrenchCommand_ty_d tp_d(::px4_msgs::msg::WrenchCommand::_tp_d_type arg)
  {
    msg_.tp_d = std::move(arg);
    return Init_WrenchCommand_ty_d(msg_);
  }

private:
  ::px4_msgs::msg::WrenchCommand msg_;
};

class Init_WrenchCommand_tr_d
{
public:
  explicit Init_WrenchCommand_tr_d(::px4_msgs::msg::WrenchCommand & msg)
  : msg_(msg)
  {}
  Init_WrenchCommand_tp_d tr_d(::px4_msgs::msg::WrenchCommand::_tr_d_type arg)
  {
    msg_.tr_d = std::move(arg);
    return Init_WrenchCommand_tp_d(msg_);
  }

private:
  ::px4_msgs::msg::WrenchCommand msg_;
};

class Init_WrenchCommand_fz_d
{
public:
  explicit Init_WrenchCommand_fz_d(::px4_msgs::msg::WrenchCommand & msg)
  : msg_(msg)
  {}
  Init_WrenchCommand_tr_d fz_d(::px4_msgs::msg::WrenchCommand::_fz_d_type arg)
  {
    msg_.fz_d = std::move(arg);
    return Init_WrenchCommand_tr_d(msg_);
  }

private:
  ::px4_msgs::msg::WrenchCommand msg_;
};

class Init_WrenchCommand_fy_d
{
public:
  explicit Init_WrenchCommand_fy_d(::px4_msgs::msg::WrenchCommand & msg)
  : msg_(msg)
  {}
  Init_WrenchCommand_fz_d fy_d(::px4_msgs::msg::WrenchCommand::_fy_d_type arg)
  {
    msg_.fy_d = std::move(arg);
    return Init_WrenchCommand_fz_d(msg_);
  }

private:
  ::px4_msgs::msg::WrenchCommand msg_;
};

class Init_WrenchCommand_fx_d
{
public:
  explicit Init_WrenchCommand_fx_d(::px4_msgs::msg::WrenchCommand & msg)
  : msg_(msg)
  {}
  Init_WrenchCommand_fy_d fx_d(::px4_msgs::msg::WrenchCommand::_fx_d_type arg)
  {
    msg_.fx_d = std::move(arg);
    return Init_WrenchCommand_fy_d(msg_);
  }

private:
  ::px4_msgs::msg::WrenchCommand msg_;
};

class Init_WrenchCommand_timestamp
{
public:
  Init_WrenchCommand_timestamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_WrenchCommand_fx_d timestamp(::px4_msgs::msg::WrenchCommand::_timestamp_type arg)
  {
    msg_.timestamp = std::move(arg);
    return Init_WrenchCommand_fx_d(msg_);
  }

private:
  ::px4_msgs::msg::WrenchCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::px4_msgs::msg::WrenchCommand>()
{
  return px4_msgs::msg::builder::Init_WrenchCommand_timestamp();
}

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__BUILDER_HPP_
