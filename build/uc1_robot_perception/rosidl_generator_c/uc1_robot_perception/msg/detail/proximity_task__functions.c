// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uc1_robot_perception:msg/ProximityTask.idl
// generated code does not contain a copyright notice
#include "uc1_robot_perception/msg/detail/proximity_task__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `min_point_robot`
// Member `min_point_vector`
#include "geometry_msgs/msg/detail/vector3__functions.h"
// Member `link_id`
#include "rosidl_runtime_c/string_functions.h"

bool
uc1_robot_perception__msg__ProximityTask__init(uc1_robot_perception__msg__ProximityTask * msg)
{
  if (!msg) {
    return false;
  }
  // min_point_robot
  if (!geometry_msgs__msg__Vector3__init(&msg->min_point_robot)) {
    uc1_robot_perception__msg__ProximityTask__fini(msg);
    return false;
  }
  // min_point_vector
  if (!geometry_msgs__msg__Vector3__init(&msg->min_point_vector)) {
    uc1_robot_perception__msg__ProximityTask__fini(msg);
    return false;
  }
  // distance
  // link_id
  if (!rosidl_runtime_c__String__init(&msg->link_id)) {
    uc1_robot_perception__msg__ProximityTask__fini(msg);
    return false;
  }
  return true;
}

void
uc1_robot_perception__msg__ProximityTask__fini(uc1_robot_perception__msg__ProximityTask * msg)
{
  if (!msg) {
    return;
  }
  // min_point_robot
  geometry_msgs__msg__Vector3__fini(&msg->min_point_robot);
  // min_point_vector
  geometry_msgs__msg__Vector3__fini(&msg->min_point_vector);
  // distance
  // link_id
  rosidl_runtime_c__String__fini(&msg->link_id);
}

bool
uc1_robot_perception__msg__ProximityTask__are_equal(const uc1_robot_perception__msg__ProximityTask * lhs, const uc1_robot_perception__msg__ProximityTask * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // min_point_robot
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->min_point_robot), &(rhs->min_point_robot)))
  {
    return false;
  }
  // min_point_vector
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->min_point_vector), &(rhs->min_point_vector)))
  {
    return false;
  }
  // distance
  if (lhs->distance != rhs->distance) {
    return false;
  }
  // link_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->link_id), &(rhs->link_id)))
  {
    return false;
  }
  return true;
}

bool
uc1_robot_perception__msg__ProximityTask__copy(
  const uc1_robot_perception__msg__ProximityTask * input,
  uc1_robot_perception__msg__ProximityTask * output)
{
  if (!input || !output) {
    return false;
  }
  // min_point_robot
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->min_point_robot), &(output->min_point_robot)))
  {
    return false;
  }
  // min_point_vector
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->min_point_vector), &(output->min_point_vector)))
  {
    return false;
  }
  // distance
  output->distance = input->distance;
  // link_id
  if (!rosidl_runtime_c__String__copy(
      &(input->link_id), &(output->link_id)))
  {
    return false;
  }
  return true;
}

uc1_robot_perception__msg__ProximityTask *
uc1_robot_perception__msg__ProximityTask__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__ProximityTask * msg = (uc1_robot_perception__msg__ProximityTask *)allocator.allocate(sizeof(uc1_robot_perception__msg__ProximityTask), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uc1_robot_perception__msg__ProximityTask));
  bool success = uc1_robot_perception__msg__ProximityTask__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uc1_robot_perception__msg__ProximityTask__destroy(uc1_robot_perception__msg__ProximityTask * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uc1_robot_perception__msg__ProximityTask__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uc1_robot_perception__msg__ProximityTask__Sequence__init(uc1_robot_perception__msg__ProximityTask__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__ProximityTask * data = NULL;

  if (size) {
    data = (uc1_robot_perception__msg__ProximityTask *)allocator.zero_allocate(size, sizeof(uc1_robot_perception__msg__ProximityTask), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uc1_robot_perception__msg__ProximityTask__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uc1_robot_perception__msg__ProximityTask__fini(&data[i - 1]);
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
uc1_robot_perception__msg__ProximityTask__Sequence__fini(uc1_robot_perception__msg__ProximityTask__Sequence * array)
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
      uc1_robot_perception__msg__ProximityTask__fini(&array->data[i]);
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

uc1_robot_perception__msg__ProximityTask__Sequence *
uc1_robot_perception__msg__ProximityTask__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__ProximityTask__Sequence * array = (uc1_robot_perception__msg__ProximityTask__Sequence *)allocator.allocate(sizeof(uc1_robot_perception__msg__ProximityTask__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uc1_robot_perception__msg__ProximityTask__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uc1_robot_perception__msg__ProximityTask__Sequence__destroy(uc1_robot_perception__msg__ProximityTask__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uc1_robot_perception__msg__ProximityTask__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uc1_robot_perception__msg__ProximityTask__Sequence__are_equal(const uc1_robot_perception__msg__ProximityTask__Sequence * lhs, const uc1_robot_perception__msg__ProximityTask__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uc1_robot_perception__msg__ProximityTask__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uc1_robot_perception__msg__ProximityTask__Sequence__copy(
  const uc1_robot_perception__msg__ProximityTask__Sequence * input,
  uc1_robot_perception__msg__ProximityTask__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uc1_robot_perception__msg__ProximityTask);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uc1_robot_perception__msg__ProximityTask * data =
      (uc1_robot_perception__msg__ProximityTask *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uc1_robot_perception__msg__ProximityTask__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uc1_robot_perception__msg__ProximityTask__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uc1_robot_perception__msg__ProximityTask__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
