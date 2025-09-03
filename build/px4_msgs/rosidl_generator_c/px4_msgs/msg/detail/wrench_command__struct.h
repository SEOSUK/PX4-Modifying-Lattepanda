// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/WrenchCommand.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/WrenchCommand in the package px4_msgs.
typedef struct px4_msgs__msg__WrenchCommand
{
  /// time since system start (microseconds)
  uint64_t timestamp;
  /// x directional body force command
  float fx_d;
  /// y directional body force command
  float fy_d;
  /// z directional body force command
  float fz_d;
  /// roll  body torque command
  float tr_d;
  /// pitch body torque command
  float tp_d;
  /// yaw   body torque command
  float ty_d;
} px4_msgs__msg__WrenchCommand;

// Struct for a sequence of px4_msgs__msg__WrenchCommand.
typedef struct px4_msgs__msg__WrenchCommand__Sequence
{
  px4_msgs__msg__WrenchCommand * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__WrenchCommand__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__WRENCH_COMMAND__STRUCT_H_
