// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/ServoAngle.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__SERVO_ANGLE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__SERVO_ANGLE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ServoAngle in the package px4_msgs.
/**
  * servo angle message
 */
typedef struct px4_msgs__msg__ServoAngle
{
  /// time since system start (microseconds)
  uint64_t timestamp;
  float servo_angle[4];
} px4_msgs__msg__ServoAngle;

// Struct for a sequence of px4_msgs__msg__ServoAngle.
typedef struct px4_msgs__msg__ServoAngle__Sequence
{
  px4_msgs__msg__ServoAngle * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__ServoAngle__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__SERVO_ANGLE__STRUCT_H_
