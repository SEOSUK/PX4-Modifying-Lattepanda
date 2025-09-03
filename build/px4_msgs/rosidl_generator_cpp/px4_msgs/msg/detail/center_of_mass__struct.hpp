// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/CenterOfMass.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__CenterOfMass __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__CenterOfMass __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CenterOfMass_
{
  using Type = CenterOfMass_<ContainerAllocator>;

  explicit CenterOfMass_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      std::fill<typename std::array<float, 3>::iterator, float>(this->present_com_hat.begin(), this->present_com_hat.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->past_com_hat.begin(), this->past_com_hat.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->com_tilde.begin(), this->com_tilde.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->com_update.begin(), this->com_update.end(), 0.0f);
    }
  }

  explicit CenterOfMass_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : present_com_hat(_alloc),
    past_com_hat(_alloc),
    com_tilde(_alloc),
    com_update(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      std::fill<typename std::array<float, 3>::iterator, float>(this->present_com_hat.begin(), this->present_com_hat.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->past_com_hat.begin(), this->past_com_hat.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->com_tilde.begin(), this->com_tilde.end(), 0.0f);
      std::fill<typename std::array<float, 3>::iterator, float>(this->com_update.begin(), this->com_update.end(), 0.0f);
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _present_com_hat_type =
    std::array<float, 3>;
  _present_com_hat_type present_com_hat;
  using _past_com_hat_type =
    std::array<float, 3>;
  _past_com_hat_type past_com_hat;
  using _com_tilde_type =
    std::array<float, 3>;
  _com_tilde_type com_tilde;
  using _com_update_type =
    std::array<float, 3>;
  _com_update_type com_update;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__present_com_hat(
    const std::array<float, 3> & _arg)
  {
    this->present_com_hat = _arg;
    return *this;
  }
  Type & set__past_com_hat(
    const std::array<float, 3> & _arg)
  {
    this->past_com_hat = _arg;
    return *this;
  }
  Type & set__com_tilde(
    const std::array<float, 3> & _arg)
  {
    this->com_tilde = _arg;
    return *this;
  }
  Type & set__com_update(
    const std::array<float, 3> & _arg)
  {
    this->com_update = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    px4_msgs::msg::CenterOfMass_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::CenterOfMass_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::CenterOfMass_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::CenterOfMass_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::CenterOfMass_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::CenterOfMass_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::CenterOfMass_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::CenterOfMass_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::CenterOfMass_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::CenterOfMass_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__CenterOfMass
    std::shared_ptr<px4_msgs::msg::CenterOfMass_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__CenterOfMass
    std::shared_ptr<px4_msgs::msg::CenterOfMass_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CenterOfMass_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->present_com_hat != other.present_com_hat) {
      return false;
    }
    if (this->past_com_hat != other.past_com_hat) {
      return false;
    }
    if (this->com_tilde != other.com_tilde) {
      return false;
    }
    if (this->com_update != other.com_update) {
      return false;
    }
    return true;
  }
  bool operator!=(const CenterOfMass_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CenterOfMass_

// alias to use template instance with default allocator
using CenterOfMass =
  px4_msgs::msg::CenterOfMass_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__STRUCT_HPP_
