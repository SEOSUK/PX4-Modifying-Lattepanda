// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/WrenchCommand.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "px4_msgs/msg/detail/wrench_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace px4_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const WrenchCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: timestamp
  {
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: fx_d
  {
    out << "fx_d: ";
    rosidl_generator_traits::value_to_yaml(msg.fx_d, out);
    out << ", ";
  }

  // member: fy_d
  {
    out << "fy_d: ";
    rosidl_generator_traits::value_to_yaml(msg.fy_d, out);
    out << ", ";
  }

  // member: fz_d
  {
    out << "fz_d: ";
    rosidl_generator_traits::value_to_yaml(msg.fz_d, out);
    out << ", ";
  }

  // member: tr_d
  {
    out << "tr_d: ";
    rosidl_generator_traits::value_to_yaml(msg.tr_d, out);
    out << ", ";
  }

  // member: tp_d
  {
    out << "tp_d: ";
    rosidl_generator_traits::value_to_yaml(msg.tp_d, out);
    out << ", ";
  }

  // member: ty_d
  {
    out << "ty_d: ";
    rosidl_generator_traits::value_to_yaml(msg.ty_d, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const WrenchCommand & msg,
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

  // member: fx_d
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fx_d: ";
    rosidl_generator_traits::value_to_yaml(msg.fx_d, out);
    out << "\n";
  }

  // member: fy_d
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fy_d: ";
    rosidl_generator_traits::value_to_yaml(msg.fy_d, out);
    out << "\n";
  }

  // member: fz_d
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fz_d: ";
    rosidl_generator_traits::value_to_yaml(msg.fz_d, out);
    out << "\n";
  }

  // member: tr_d
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tr_d: ";
    rosidl_generator_traits::value_to_yaml(msg.tr_d, out);
    out << "\n";
  }

  // member: tp_d
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tp_d: ";
    rosidl_generator_traits::value_to_yaml(msg.tp_d, out);
    out << "\n";
  }

  // member: ty_d
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ty_d: ";
    rosidl_generator_traits::value_to_yaml(msg.ty_d, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WrenchCommand & msg, bool use_flow_style = false)
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
  const px4_msgs::msg::WrenchCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  px4_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use px4_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const px4_msgs::msg::WrenchCommand & msg)
{
  return px4_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<px4_msgs::msg::WrenchCommand>()
{
  return "px4_msgs::msg::WrenchCommand";
}

template<>
inline const char * name<px4_msgs::msg::WrenchCommand>()
{
  return "px4_msgs/msg/WrenchCommand";
}

template<>
struct has_fixed_size<px4_msgs::msg::WrenchCommand>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<px4_msgs::msg::WrenchCommand>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<px4_msgs::msg::WrenchCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__TRAITS_HPP_
