// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/WrenchCommand.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__WrenchCommand __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__WrenchCommand __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WrenchCommand_
{
  using Type = WrenchCommand_<ContainerAllocator>;

  explicit WrenchCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->fx_d = 0.0f;
      this->fy_d = 0.0f;
      this->fz_d = 0.0f;
      this->tr_d = 0.0f;
      this->tp_d = 0.0f;
      this->ty_d = 0.0f;
    }
  }

  explicit WrenchCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->fx_d = 0.0f;
      this->fy_d = 0.0f;
      this->fz_d = 0.0f;
      this->tr_d = 0.0f;
      this->tp_d = 0.0f;
      this->ty_d = 0.0f;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _fx_d_type =
    float;
  _fx_d_type fx_d;
  using _fy_d_type =
    float;
  _fy_d_type fy_d;
  using _fz_d_type =
    float;
  _fz_d_type fz_d;
  using _tr_d_type =
    float;
  _tr_d_type tr_d;
  using _tp_d_type =
    float;
  _tp_d_type tp_d;
  using _ty_d_type =
    float;
  _ty_d_type ty_d;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__fx_d(
    const float & _arg)
  {
    this->fx_d = _arg;
    return *this;
  }
  Type & set__fy_d(
    const float & _arg)
  {
    this->fy_d = _arg;
    return *this;
  }
  Type & set__fz_d(
    const float & _arg)
  {
    this->fz_d = _arg;
    return *this;
  }
  Type & set__tr_d(
    const float & _arg)
  {
    this->tr_d = _arg;
    return *this;
  }
  Type & set__tp_d(
    const float & _arg)
  {
    this->tp_d = _arg;
    return *this;
  }
  Type & set__ty_d(
    const float & _arg)
  {
    this->ty_d = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::WrenchCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::WrenchCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::WrenchCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::WrenchCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::WrenchCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::WrenchCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::WrenchCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::WrenchCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::WrenchCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::WrenchCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__WrenchCommand
    std::shared_ptr<px4_msgs::msg::WrenchCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__WrenchCommand
    std::shared_ptr<px4_msgs::msg::WrenchCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WrenchCommand_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->fx_d != other.fx_d) {
      return false;
    }
    if (this->fy_d != other.fy_d) {
      return false;
    }
    if (this->fz_d != other.fz_d) {
      return false;
    }
    if (this->tr_d != other.tr_d) {
      return false;
    }
    if (this->tp_d != other.tp_d) {
      return false;
    }
    if (this->ty_d != other.ty_d) {
      return false;
    }
    return true;
  }
  bool operator!=(const WrenchCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WrenchCommand_

// alias to use template instance with default allocator
using WrenchCommand =
  px4_msgs::msg::WrenchCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__STRUCT_HPP_
