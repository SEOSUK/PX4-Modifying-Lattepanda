// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from px4_msgs:msg/CenterOfMass.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__TRAITS_HPP_
#define PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "px4_msgs/msg/detail/center_of_mass__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace px4_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const CenterOfMass & msg,
  std::ostream & out)
{
  out << "{";
  // member: timestamp
  {
    out << "timestamp: ";
    rosidl_generator_traits::value_to_yaml(msg.timestamp, out);
    out << ", ";
  }

  // member: present_com_hat
  {
    if (msg.present_com_hat.size() == 0) {
      out << "present_com_hat: []";
    } else {
      out << "present_com_hat: [";
      size_t pending_items = msg.present_com_hat.size();
      for (auto item : msg.present_com_hat) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: past_com_hat
  {
    if (msg.past_com_hat.size() == 0) {
      out << "past_com_hat: []";
    } else {
      out << "past_com_hat: [";
      size_t pending_items = msg.past_com_hat.size();
      for (auto item : msg.past_com_hat) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: com_tilde
  {
    if (msg.com_tilde.size() == 0) {
      out << "com_tilde: []";
    } else {
      out << "com_tilde: [";
      size_t pending_items = msg.com_tilde.size();
      for (auto item : msg.com_tilde) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: com_update
  {
    if (msg.com_update.size() == 0) {
      out << "com_update: []";
    } else {
      out << "com_update: [";
      size_t pending_items = msg.com_update.size();
      for (auto item : msg.com_update) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CenterOfMass & msg,
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

  // member: present_com_hat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.present_com_hat.size() == 0) {
      out << "present_com_hat: []\n";
    } else {
      out << "present_com_hat:\n";
      for (auto item : msg.present_com_hat) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: past_com_hat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.past_com_hat.size() == 0) {
      out << "past_com_hat: []\n";
    } else {
      out << "past_com_hat:\n";
      for (auto item : msg.past_com_hat) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: com_tilde
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.com_tilde.size() == 0) {
      out << "com_tilde: []\n";
    } else {
      out << "com_tilde:\n";
      for (auto item : msg.com_tilde) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: com_update
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.com_update.size() == 0) {
      out << "com_update: []\n";
    } else {
      out << "com_update:\n";
      for (auto item : msg.com_update) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CenterOfMass & msg, bool use_flow_style = false)
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
  const px4_msgs::msg::CenterOfMass & msg,
  std::ostream & out, size_t indentation = 0)
{
  px4_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use px4_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const px4_msgs::msg::CenterOfMass & msg)
{
  return px4_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<px4_msgs::msg::CenterOfMass>()
{
  return "px4_msgs::msg::CenterOfMass";
}

template<>
inline const char * name<px4_msgs::msg::CenterOfMass>()
{
  return "px4_msgs/msg/CenterOfMass";
}

template<>
struct has_fixed_size<px4_msgs::msg::CenterOfMass>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<px4_msgs::msg::CenterOfMass>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<px4_msgs::msg::CenterOfMass>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__TRAITS_HPP_
