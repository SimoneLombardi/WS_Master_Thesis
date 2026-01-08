// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotOrient.idl
// generated code does not contain a copyright notice
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_orient__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__init(uc1_robot_controllers_interfaces__msg__MoveRobotOrient * msg)
{
  if (!msg) {
    return false;
  }
  // roll
  // pitch
  // yaw
  return true;
}

void
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__fini(uc1_robot_controllers_interfaces__msg__MoveRobotOrient * msg)
{
  if (!msg) {
    return;
  }
  // roll
  // pitch
  // yaw
}

bool
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__are_equal(const uc1_robot_controllers_interfaces__msg__MoveRobotOrient * lhs, const uc1_robot_controllers_interfaces__msg__MoveRobotOrient * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // roll
  if (lhs->roll != rhs->roll) {
    return false;
  }
  // pitch
  if (lhs->pitch != rhs->pitch) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  return true;
}

bool
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__copy(
  const uc1_robot_controllers_interfaces__msg__MoveRobotOrient * input,
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient * output)
{
  if (!input || !output) {
    return false;
  }
  // roll
  output->roll = input->roll;
  // pitch
  output->pitch = input->pitch;
  // yaw
  output->yaw = input->yaw;
  return true;
}

uc1_robot_controllers_interfaces__msg__MoveRobotOrient *
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient * msg = (uc1_robot_controllers_interfaces__msg__MoveRobotOrient *)allocator.allocate(sizeof(uc1_robot_controllers_interfaces__msg__MoveRobotOrient), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uc1_robot_controllers_interfaces__msg__MoveRobotOrient));
  bool success = uc1_robot_controllers_interfaces__msg__MoveRobotOrient__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__destroy(uc1_robot_controllers_interfaces__msg__MoveRobotOrient * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uc1_robot_controllers_interfaces__msg__MoveRobotOrient__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence__init(uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient * data = NULL;

  if (size) {
    data = (uc1_robot_controllers_interfaces__msg__MoveRobotOrient *)allocator.zero_allocate(size, sizeof(uc1_robot_controllers_interfaces__msg__MoveRobotOrient), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uc1_robot_controllers_interfaces__msg__MoveRobotOrient__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uc1_robot_controllers_interfaces__msg__MoveRobotOrient__fini(&data[i - 1]);
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
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence__fini(uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence * array)
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
      uc1_robot_controllers_interfaces__msg__MoveRobotOrient__fini(&array->data[i]);
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

uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence *
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence * array = (uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence *)allocator.allocate(sizeof(uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence__destroy(uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence__are_equal(const uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence * lhs, const uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uc1_robot_controllers_interfaces__msg__MoveRobotOrient__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence__copy(
  const uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence * input,
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uc1_robot_controllers_interfaces__msg__MoveRobotOrient);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uc1_robot_controllers_interfaces__msg__MoveRobotOrient * data =
      (uc1_robot_controllers_interfaces__msg__MoveRobotOrient *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uc1_robot_controllers_interfaces__msg__MoveRobotOrient__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uc1_robot_controllers_interfaces__msg__MoveRobotOrient__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uc1_robot_controllers_interfaces__msg__MoveRobotOrient__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
