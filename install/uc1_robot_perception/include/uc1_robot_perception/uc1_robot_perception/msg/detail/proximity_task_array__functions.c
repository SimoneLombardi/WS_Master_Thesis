// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uc1_robot_perception:msg/ProximityTaskArray.idl
// generated code does not contain a copyright notice
#include "uc1_robot_perception/msg/detail/proximity_task_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `proximity_tasks`
#include "uc1_robot_perception/msg/detail/proximity_task__functions.h"

bool
uc1_robot_perception__msg__ProximityTaskArray__init(uc1_robot_perception__msg__ProximityTaskArray * msg)
{
  if (!msg) {
    return false;
  }
  // proximity_tasks
  if (!uc1_robot_perception__msg__ProximityTask__Sequence__init(&msg->proximity_tasks, 0)) {
    uc1_robot_perception__msg__ProximityTaskArray__fini(msg);
    return false;
  }
  return true;
}

void
uc1_robot_perception__msg__ProximityTaskArray__fini(uc1_robot_perception__msg__ProximityTaskArray * msg)
{
  if (!msg) {
    return;
  }
  // proximity_tasks
  uc1_robot_perception__msg__ProximityTask__Sequence__fini(&msg->proximity_tasks);
}

bool
uc1_robot_perception__msg__ProximityTaskArray__are_equal(const uc1_robot_perception__msg__ProximityTaskArray * lhs, const uc1_robot_perception__msg__ProximityTaskArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // proximity_tasks
  if (!uc1_robot_perception__msg__ProximityTask__Sequence__are_equal(
      &(lhs->proximity_tasks), &(rhs->proximity_tasks)))
  {
    return false;
  }
  return true;
}

bool
uc1_robot_perception__msg__ProximityTaskArray__copy(
  const uc1_robot_perception__msg__ProximityTaskArray * input,
  uc1_robot_perception__msg__ProximityTaskArray * output)
{
  if (!input || !output) {
    return false;
  }
  // proximity_tasks
  if (!uc1_robot_perception__msg__ProximityTask__Sequence__copy(
      &(input->proximity_tasks), &(output->proximity_tasks)))
  {
    return false;
  }
  return true;
}

uc1_robot_perception__msg__ProximityTaskArray *
uc1_robot_perception__msg__ProximityTaskArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__ProximityTaskArray * msg = (uc1_robot_perception__msg__ProximityTaskArray *)allocator.allocate(sizeof(uc1_robot_perception__msg__ProximityTaskArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uc1_robot_perception__msg__ProximityTaskArray));
  bool success = uc1_robot_perception__msg__ProximityTaskArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uc1_robot_perception__msg__ProximityTaskArray__destroy(uc1_robot_perception__msg__ProximityTaskArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uc1_robot_perception__msg__ProximityTaskArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uc1_robot_perception__msg__ProximityTaskArray__Sequence__init(uc1_robot_perception__msg__ProximityTaskArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__ProximityTaskArray * data = NULL;

  if (size) {
    data = (uc1_robot_perception__msg__ProximityTaskArray *)allocator.zero_allocate(size, sizeof(uc1_robot_perception__msg__ProximityTaskArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uc1_robot_perception__msg__ProximityTaskArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uc1_robot_perception__msg__ProximityTaskArray__fini(&data[i - 1]);
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
uc1_robot_perception__msg__ProximityTaskArray__Sequence__fini(uc1_robot_perception__msg__ProximityTaskArray__Sequence * array)
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
      uc1_robot_perception__msg__ProximityTaskArray__fini(&array->data[i]);
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

uc1_robot_perception__msg__ProximityTaskArray__Sequence *
uc1_robot_perception__msg__ProximityTaskArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__ProximityTaskArray__Sequence * array = (uc1_robot_perception__msg__ProximityTaskArray__Sequence *)allocator.allocate(sizeof(uc1_robot_perception__msg__ProximityTaskArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uc1_robot_perception__msg__ProximityTaskArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uc1_robot_perception__msg__ProximityTaskArray__Sequence__destroy(uc1_robot_perception__msg__ProximityTaskArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uc1_robot_perception__msg__ProximityTaskArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uc1_robot_perception__msg__ProximityTaskArray__Sequence__are_equal(const uc1_robot_perception__msg__ProximityTaskArray__Sequence * lhs, const uc1_robot_perception__msg__ProximityTaskArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uc1_robot_perception__msg__ProximityTaskArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uc1_robot_perception__msg__ProximityTaskArray__Sequence__copy(
  const uc1_robot_perception__msg__ProximityTaskArray__Sequence * input,
  uc1_robot_perception__msg__ProximityTaskArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uc1_robot_perception__msg__ProximityTaskArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uc1_robot_perception__msg__ProximityTaskArray * data =
      (uc1_robot_perception__msg__ProximityTaskArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uc1_robot_perception__msg__ProximityTaskArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uc1_robot_perception__msg__ProximityTaskArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uc1_robot_perception__msg__ProximityTaskArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
