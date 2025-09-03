// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/CustomControlMode.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CUSTOM_CONTROL_MODE__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__CUSTOM_CONTROL_MODE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "px4_msgs/msg/detail/custom_control_mode__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace px4_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const CustomControlMode & msg,
  std::ostream & out)
{
  out << "{";
  // member: timestamp
  {
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: disturbance_observer_flag
  {
    out << "disturbance_observer_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.disturbance_observer_flag, out);
    out << ", ";
  }

  // member: custom_mode_flag
  {
    out << "custom_mode_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_mode_flag, out);
    out << ", ";
  }

  // member: sine_motion_flag
  {
    out << "sine_motion_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.sine_motion_flag, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CustomControlMode & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << "\n";
  }

  // member: disturbance_observer_flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "disturbance_observer_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.disturbance_observer_flag, out);
    out << "\n";
  }

  // member: custom_mode_flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "custom_mode_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.custom_mode_flag, out);
    out << "\n";
  }

  // member: sine_motion_flag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sine_motion_flag: ";
    rosidl_generator_traits::value_to_yaml(msg.sine_motion_flag, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CustomControlMode & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace px4_msgs

namespace rosidl_generator_traits
{

[[deprecated("use px4_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const px4_msgs::msg::CustomControlMode & msg,
  std::ostream & out, size_t indentation = 0)
{
  px4_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use px4_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const px4_msgs::msg::CustomControlMode & msg)
{
  return px4_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<px4_msgs::msg::CustomControlMode>()
{
  return "px4_msgs::msg::CustomControlMode";
}

template<>
inline const char * name<px4_msgs::msg::CustomControlMode>()
{
  return "px4_msgs/msg/CustomControlMode";
}

template<>
struct has_fixed_size<px4_msgs::msg::CustomControlMode>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<px4_msgs::msg::CustomControlMode>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<px4_msgs::msg::CustomControlMode>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__CUSTOM_CONTROL_MODE__TRAITS_HPP_
