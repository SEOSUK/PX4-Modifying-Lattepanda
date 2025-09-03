// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/MocapPose.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__MOCAP_POSE__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__MOCAP_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MocapPose in the package px4_msgs.
typedef struct px4_msgs__msg__MocapPose
{
  /// time since system start (microseconds)
  uint64_t timestamp;
  /// global x directional position
  float x;
  /// global y directional position
  float y;
  /// global z directional position
  float z;
  /// quternion x
  float rx;
  /// quternion y
  float ry;
  /// quternion z
  float rz;
  /// quternion w
  float rw;
} px4_msgs__msg__MocapPose;

// Struct for a sequence of px4_msgs__msg__MocapPose.
typedef struct px4_msgs__msg__MocapPose__Sequence
{
  px4_msgs__msg__MocapPose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__MocapPose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__MOCAP_POSE__STRUCT_H_
