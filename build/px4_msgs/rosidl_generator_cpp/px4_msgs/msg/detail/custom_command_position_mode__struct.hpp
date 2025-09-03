// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/CustomCommandPositionMode.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CUSTOM_COMMAND_POSITION_MODE__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__CUSTOM_COMMAND_POSITION_MODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__CustomCommandPositionMode __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__CustomCommandPositionMode __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CustomCommandPositionMode_
{
  using Type = CustomCommandPositionMode_<ContainerAllocator>;

  explicit CustomCommandPositionMode_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      std::fill<typename std::array<float, 4>::iterator, float>(this->setpoint.begin(), this->setpoint.end(), 0.0f);
    }
  }

  explicit CustomCommandPositionMode_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : setpoint(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      std::fill<typename std::array<float, 4>::iterator, float>(this->setpoint.begin(), this->setpoint.end(), 0.0f);
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _setpoint_type =
    std::array<float, 4>;
  _setpoint_type setpoint;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__setpoint(
    const std::array<float, 4> & _arg)
  {
    this->setpoint = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__CustomCommandPositionMode
    std::shared_ptr<px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__CustomCommandPositionMode
    std::shared_ptr<px4_msgs::msg::CustomCommandPositionMode_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CustomCommandPositionMode_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->setpoint != other.setpoint) {
      return false;
    }
    return true;
  }
  bool operator!=(const CustomCommandPositionMode_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CustomCommandPositionMode_

// alias to use template instance with default allocator
using CustomCommandPositionMode =
  px4_msgs::msg::CustomCommandPositionMode_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__CUSTOM_COMMAND_POSITION_MODE__STRUCT_HPP_
