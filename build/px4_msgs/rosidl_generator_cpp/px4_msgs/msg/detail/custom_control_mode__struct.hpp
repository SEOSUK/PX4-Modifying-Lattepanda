// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/CustomControlMode.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CUSTOM_CONTROL_MODE__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__CUSTOM_CONTROL_MODE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__CustomControlMode __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__CustomControlMode __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CustomControlMode_
{
  using Type = CustomControlMode_<ContainerAllocator>;

  explicit CustomControlMode_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->disturbance_observer_flag = false;
      this->custom_mode_flag = false;
      this->sine_motion_flag = false;
    }
  }

  explicit CustomControlMode_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->disturbance_observer_flag = false;
      this->custom_mode_flag = false;
      this->sine_motion_flag = false;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _disturbance_observer_flag_type =
    bool;
  _disturbance_observer_flag_type disturbance_observer_flag;
  using _custom_mode_flag_type =
    bool;
  _custom_mode_flag_type custom_mode_flag;
  using _sine_motion_flag_type =
    bool;
  _sine_motion_flag_type sine_motion_flag;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__disturbance_observer_flag(
    const bool & _arg)
  {
    this->disturbance_observer_flag = _arg;
    return *this;
  }
  Type & set__custom_mode_flag(
    const bool & _arg)
  {
    this->custom_mode_flag = _arg;
    return *this;
  }
  Type & set__sine_motion_flag(
    const bool & _arg)
  {
    this->sine_motion_flag = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::CustomControlMode_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::CustomControlMode_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::CustomControlMode_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::CustomControlMode_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::CustomControlMode_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::CustomControlMode_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::CustomControlMode_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::CustomControlMode_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::CustomControlMode_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::CustomControlMode_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__CustomControlMode
    std::shared_ptr<px4_msgs::msg::CustomControlMode_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__CustomControlMode
    std::shared_ptr<px4_msgs::msg::CustomControlMode_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CustomControlMode_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->disturbance_observer_flag != other.disturbance_observer_flag) {
      return false;
    }
    if (this->custom_mode_flag != other.custom_mode_flag) {
      return false;
    }
    if (this->sine_motion_flag != other.sine_motion_flag) {
      return false;
    }
    return true;
  }
  bool operator!=(const CustomControlMode_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CustomControlMode_

// alias to use template instance with default allocator
using CustomControlMode =
  px4_msgs::msg::CustomControlMode_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__CUSTOM_CONTROL_MODE__STRUCT_HPP_
