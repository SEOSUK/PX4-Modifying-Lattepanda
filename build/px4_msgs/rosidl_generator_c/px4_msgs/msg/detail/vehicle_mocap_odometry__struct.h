// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/VehicleMocapOdometry.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_MOCAP_ODOMETRY__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_MOCAP_ODOMETRY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/VehicleMocapOdometry in the package px4_msgs.
typedef struct px4_msgs__msg__VehicleMocapOdometry
{
  /// 시간 (uORB publish 시간)
  uint64_t timestamp;
  /// 실제 센서 수집 시간
  uint64_t timestamp_sample;
  /// 위치/자세 기준 좌표계 (e.g. NED, FRD 등)
  uint8_t pose_frame;
  /// x, y, z 위치
  float position[3];
  /// 자세 (quaternion, [w, x, y, z] 또는 [x, y, z, w])
  float q[4];
  /// x, y, z 속도
  float velocity[3];
  /// body frame 기준 각속도
  float angular_velocity[3];
  /// 위치 신뢰도 (분산 값)
  float position_variance[3];
  /// 자세 신뢰도 (분산 값)
  float orientation_variance[3];
  /// 속도 신뢰도 (분산 값)
  float velocity_variance[3];
  /// 각속도 신뢰도 (분산 값)
  float angular_velocity_variance[3];
  /// EKF 리셋 횟수 추적용
  uint8_t reset_counter;
  /// 트래킹 품질 좋음/나쁨 여부
  bool quality_flag;
} px4_msgs__msg__VehicleMocapOdometry;

// Struct for a sequence of px4_msgs__msg__VehicleMocapOdometry.
typedef struct px4_msgs__msg__VehicleMocapOdometry__Sequence
{
  px4_msgs__msg__VehicleMocapOdometry * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__VehicleMocapOdometry__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_MOCAP_ODOMETRY__STRUCT_H_
