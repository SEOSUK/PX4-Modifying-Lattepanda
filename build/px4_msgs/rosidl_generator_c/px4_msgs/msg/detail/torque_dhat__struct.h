// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/TorqueDhat.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__TORQUE_DHAT__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__TORQUE_DHAT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/TorqueDhat in the package px4_msgs.
/**
  * torque disturbance message
 */
typedef struct px4_msgs__msg__TorqueDhat
{
  /// time since system start (microseconds)
  uint64_t timestamp;
  float xyz[3];
} px4_msgs__msg__TorqueDhat;

// Struct for a sequence of px4_msgs__msg__TorqueDhat.
typedef struct px4_msgs__msg__TorqueDhat__Sequence
{
  px4_msgs__msg__TorqueDhat * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__TorqueDhat__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__TORQUE_DHAT__STRUCT_H_
