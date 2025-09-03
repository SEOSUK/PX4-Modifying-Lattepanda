// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from px4_msgs:msg/CustomCommandPositionMode.idl
// generated code does not contain a copyright notice
#include "px4_msgs/msg/detail/custom_command_position_mode__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
px4_msgs__msg__CustomCommandPositionMode__init(px4_msgs__msg__CustomCommandPositionMode * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  // setpoint
  return true;
}

void
px4_msgs__msg__CustomCommandPositionMode__fini(px4_msgs__msg__CustomCommandPositionMode * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  // setpoint
}

bool
px4_msgs__msg__CustomCommandPositionMode__are_equal(const px4_msgs__msg__CustomCommandPositionMode * lhs, const px4_msgs__msg__CustomCommandPositionMode * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  // setpoint
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->setpoint[i] != rhs->setpoint[i]) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__CustomCommandPositionMode__copy(
  const px4_msgs__msg__CustomCommandPositionMode * input,
  px4_msgs__msg__CustomCommandPositionMode * output)
{
  if (!input || !output) {
    return false;
  }
  // timestamp
  output->timestamp = input->timestamp;
  // setpoint
  for (size_t i = 0; i < 4; ++i) {
    output->setpoint[i] = input->setpoint[i];
  }
  return true;
}

px4_msgs__msg__CustomCommandPositionMode *
px4_msgs__msg__CustomCommandPositionMode__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__CustomCommandPositionMode * msg = (px4_msgs__msg__CustomCommandPositionMode *)allocator.allocate(sizeof(px4_msgs__msg__CustomCommandPositionMode), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(px4_msgs__msg__CustomCommandPositionMode));
  bool success = px4_msgs__msg__CustomCommandPositionMode__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
px4_msgs__msg__CustomCommandPositionMode__destroy(px4_msgs__msg__CustomCommandPositionMode * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    px4_msgs__msg__CustomCommandPositionMode__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
px4_msgs__msg__CustomCommandPositionMode__Sequence__init(px4_msgs__msg__CustomCommandPositionMode__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__CustomCommandPositionMode * data = NULL;

  if (size) {
    data = (px4_msgs__msg__CustomCommandPositionMode *)allocator.zero_allocate(size, sizeof(px4_msgs__msg__CustomCommandPositionMode), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = px4_msgs__msg__CustomCommandPositionMode__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        px4_msgs__msg__CustomCommandPositionMode__fini(&data[i - 1]);
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
px4_msgs__msg__CustomCommandPositionMode__Sequence__fini(px4_msgs__msg__CustomCommandPositionMode__Sequence * array)
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
      px4_msgs__msg__CustomCommandPositionMode__fini(&array->data[i]);
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

px4_msgs__msg__CustomCommandPositionMode__Sequence *
px4_msgs__msg__CustomCommandPositionMode__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__CustomCommandPositionMode__Sequence * array = (px4_msgs__msg__CustomCommandPositionMode__Sequence *)allocator.allocate(sizeof(px4_msgs__msg__CustomCommandPositionMode__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = px4_msgs__msg__CustomCommandPositionMode__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
px4_msgs__msg__CustomCommandPositionMode__Sequence__destroy(px4_msgs__msg__CustomCommandPositionMode__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    px4_msgs__msg__CustomCommandPositionMode__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
px4_msgs__msg__CustomCommandPositionMode__Sequence__are_equal(const px4_msgs__msg__CustomCommandPositionMode__Sequence * lhs, const px4_msgs__msg__CustomCommandPositionMode__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!px4_msgs__msg__CustomCommandPositionMode__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__CustomCommandPositionMode__Sequence__copy(
  const px4_msgs__msg__CustomCommandPositionMode__Sequence * input,
  px4_msgs__msg__CustomCommandPositionMode__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(px4_msgs__msg__CustomCommandPositionMode);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    px4_msgs__msg__CustomCommandPositionMode * data =
      (px4_msgs__msg__CustomCommandPositionMode *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!px4_msgs__msg__CustomCommandPositionMode__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          px4_msgs__msg__CustomCommandPositionMode__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!px4_msgs__msg__CustomCommandPositionMode__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
