// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/CustomCommandPositionMode.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CUSTOM_COMMAND_POSITION_MODE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__CUSTOM_COMMAND_POSITION_MODE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/CustomCommandPositionMode in the package px4_msgs.
/**
  * custom command position mode seuk
 */
typedef struct px4_msgs__msg__CustomCommandPositionMode
{
  uint64_t timestamp;
  /// [x_des, y_des, z_des, yaw_des]
  float setpoint[4];
} px4_msgs__msg__CustomCommandPositionMode;

// Struct for a sequence of px4_msgs__msg__CustomCommandPositionMode.
typedef struct px4_msgs__msg__CustomCommandPositionMode__Sequence
{
  px4_msgs__msg__CustomCommandPositionMode * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__CustomCommandPositionMode__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__CUSTOM_COMMAND_POSITION_MODE__STRUCT_H_
