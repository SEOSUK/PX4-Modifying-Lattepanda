// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/ServoAngle.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__SERVO_ANGLE__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__SERVO_ANGLE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__ServoAngle __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__ServoAngle __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServoAngle_
{
  using Type = ServoAngle_<ContainerAllocator>;

  explicit ServoAngle_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      std::fill<typename std::array<float, 4>::iterator, float>(this->servo_angle.begin(), this->servo_angle.end(), 0.0f);
    }
  }

  explicit ServoAngle_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : servo_angle(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      std::fill<typename std::array<float, 4>::iterator, float>(this->servo_angle.begin(), this->servo_angle.end(), 0.0f);
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _servo_angle_type =
    std::array<float, 4>;
  _servo_angle_type servo_angle;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__servo_angle(
    const std::array<float, 4> & _arg)
  {
    this->servo_angle = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::ServoAngle_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::ServoAngle_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::ServoAngle_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::ServoAngle_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::ServoAngle_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::ServoAngle_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::ServoAngle_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::ServoAngle_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::ServoAngle_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::ServoAngle_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__ServoAngle
    std::shared_ptr<px4_msgs::msg::ServoAngle_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__ServoAngle
    std::shared_ptr<px4_msgs::msg::ServoAngle_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoAngle_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->servo_angle != other.servo_angle) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoAngle_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoAngle_

// alias to use template instance with default allocator
using ServoAngle =
  px4_msgs::msg::ServoAngle_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__SERVO_ANGLE__STRUCT_HPP_
