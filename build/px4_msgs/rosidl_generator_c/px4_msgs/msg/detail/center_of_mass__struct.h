// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/CenterOfMass.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/CenterOfMass in the package px4_msgs.
/**
  * center of mass message
 */
typedef struct px4_msgs__msg__CenterOfMass
{
  /// time since system start (microseconds)
  uint64_t timestamp;
  float present_com_hat[3];
  float past_com_hat[3];
  float com_tilde[3];
  float com_update[3];
} px4_msgs__msg__CenterOfMass;

// Struct for a sequence of px4_msgs__msg__CenterOfMass.
typedef struct px4_msgs__msg__CenterOfMass__Sequence
{
  px4_msgs__msg__CenterOfMass * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__CenterOfMass__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__CENTER_OF_MASS__STRUCT_H_
