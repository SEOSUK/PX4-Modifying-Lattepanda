// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from px4_msgs:msg/VehicleMocapOdometry.idl
// generated code does not contain a copyright notice
#include "px4_msgs/msg/detail/vehicle_mocap_odometry__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
px4_msgs__msg__VehicleMocapOdometry__init(px4_msgs__msg__VehicleMocapOdometry * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  // timestamp_sample
  // pose_frame
  // position
  // q
  // velocity
  // angular_velocity
  // position_variance
  // orientation_variance
  // velocity_variance
  // angular_velocity_variance
  // reset_counter
  // quality_flag
  return true;
}

void
px4_msgs__msg__VehicleMocapOdometry__fini(px4_msgs__msg__VehicleMocapOdometry * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  // timestamp_sample
  // pose_frame
  // position
  // q
  // velocity
  // angular_velocity
  // position_variance
  // orientation_variance
  // velocity_variance
  // angular_velocity_variance
  // reset_counter
  // quality_flag
}

bool
px4_msgs__msg__VehicleMocapOdometry__are_equal(const px4_msgs__msg__VehicleMocapOdometry * lhs, const px4_msgs__msg__VehicleMocapOdometry * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  // timestamp_sample
  if (lhs->timestamp_sample != rhs->timestamp_sample) {
    return false;
  }
  // pose_frame
  if (lhs->pose_frame != rhs->pose_frame) {
    return false;
  }
  // position
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->position[i] != rhs->position[i]) {
      return false;
    }
  }
  // q
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->q[i] != rhs->q[i]) {
      return false;
    }
  }
  // velocity
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->velocity[i] != rhs->velocity[i]) {
      return false;
    }
  }
  // angular_velocity
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->angular_velocity[i] != rhs->angular_velocity[i]) {
      return false;
    }
  }
  // position_variance
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->position_variance[i] != rhs->position_variance[i]) {
      return false;
    }
  }
  // orientation_variance
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->orientation_variance[i] != rhs->orientation_variance[i]) {
      return false;
    }
  }
  // velocity_variance
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->velocity_variance[i] != rhs->velocity_variance[i]) {
      return false;
    }
  }
  // angular_velocity_variance
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->angular_velocity_variance[i] != rhs->angular_velocity_variance[i]) {
      return false;
    }
  }
  // reset_counter
  if (lhs->reset_counter != rhs->reset_counter) {
    return false;
  }
  // quality_flag
  if (lhs->quality_flag != rhs->quality_flag) {
    return false;
  }
  return true;
}

bool
px4_msgs__msg__VehicleMocapOdometry__copy(
  const px4_msgs__msg__VehicleMocapOdometry * input,
  px4_msgs__msg__VehicleMocapOdometry * output)
{
  if (!input || !output) {
    return false;
  }
  // timestamp
  output->timestamp = input->timestamp;
  // timestamp_sample
  output->timestamp_sample = input->timestamp_sample;
  // pose_frame
  output->pose_frame = input->pose_frame;
  // position
  for (size_t i = 0; i < 3; ++i) {
    output->position[i] = input->position[i];
  }
  // q
  for (size_t i = 0; i < 4; ++i) {
    output->q[i] = input->q[i];
  }
  // velocity
  for (size_t i = 0; i < 3; ++i) {
    output->velocity[i] = input->velocity[i];
  }
  // angular_velocity
  for (size_t i = 0; i < 3; ++i) {
    output->angular_velocity[i] = input->angular_velocity[i];
  }
  // position_variance
  for (size_t i = 0; i < 3; ++i) {
    output->position_variance[i] = input->position_variance[i];
  }
  // orientation_variance
  for (size_t i = 0; i < 3; ++i) {
    output->orientation_variance[i] = input->orientation_variance[i];
  }
  // velocity_variance
  for (size_t i = 0; i < 3; ++i) {
    output->velocity_variance[i] = input->velocity_variance[i];
  }
  // angular_velocity_variance
  for (size_t i = 0; i < 3; ++i) {
    output->angular_velocity_variance[i] = input->angular_velocity_variance[i];
  }
  // reset_counter
  output->reset_counter = input->reset_counter;
  // quality_flag
  output->quality_flag = input->quality_flag;
  return true;
}

px4_msgs__msg__VehicleMocapOdometry *
px4_msgs__msg__VehicleMocapOdometry__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__VehicleMocapOdometry * msg = (px4_msgs__msg__VehicleMocapOdometry *)allocator.allocate(sizeof(px4_msgs__msg__VehicleMocapOdometry), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(px4_msgs__msg__VehicleMocapOdometry));
  bool success = px4_msgs__msg__VehicleMocapOdometry__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
px4_msgs__msg__VehicleMocapOdometry__destroy(px4_msgs__msg__VehicleMocapOdometry * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    px4_msgs__msg__VehicleMocapOdometry__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
px4_msgs__msg__VehicleMocapOdometry__Sequence__init(px4_msgs__msg__VehicleMocapOdometry__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__VehicleMocapOdometry * data = NULL;

  if (size) {
    data = (px4_msgs__msg__VehicleMocapOdometry *)allocator.zero_allocate(size, sizeof(px4_msgs__msg__VehicleMocapOdometry), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = px4_msgs__msg__VehicleMocapOdometry__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        px4_msgs__msg__VehicleMocapOdometry__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
px4_msgs__msg__VehicleMocapOdometry__Sequence__fini(px4_msgs__msg__VehicleMocapOdometry__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      px4_msgs__msg__VehicleMocapOdometry__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

px4_msgs__msg__VehicleMocapOdometry__Sequence *
px4_msgs__msg__VehicleMocapOdometry__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__VehicleMocapOdometry__Sequence * array = (px4_msgs__msg__VehicleMocapOdometry__Sequence *)allocator.allocate(sizeof(px4_msgs__msg__VehicleMocapOdometry__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = px4_msgs__msg__VehicleMocapOdometry__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
px4_msgs__msg__VehicleMocapOdometry__Sequence__destroy(px4_msgs__msg__VehicleMocapOdometry__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    px4_msgs__msg__VehicleMocapOdometry__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
px4_msgs__msg__VehicleMocapOdometry__Sequence__are_equal(const px4_msgs__msg__VehicleMocapOdometry__Sequence * lhs, const px4_msgs__msg__VehicleMocapOdometry__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!px4_msgs__msg__VehicleMocapOdometry__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__VehicleMocapOdometry__Sequence__copy(
  const px4_msgs__msg__VehicleMocapOdometry__Sequence * input,
  px4_msgs__msg__VehicleMocapOdometry__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(px4_msgs__msg__VehicleMocapOdometry);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    px4_msgs__msg__VehicleMocapOdometry * data =
      (px4_msgs__msg__VehicleMocapOdometry *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!px4_msgs__msg__VehicleMocapOdometry__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          px4_msgs__msg__VehicleMocapOdometry__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!px4_msgs__msg__VehicleMocapOdometry__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
