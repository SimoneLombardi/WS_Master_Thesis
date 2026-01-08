// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uc1_robot_perception:msg/Contact.idl
// generated code does not contain a copyright notice
#include "uc1_robot_perception/msg/detail/contact__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `contact_location`
// Member `contact_normal`
#include "geometry_msgs/msg/detail/vector3__functions.h"
// Member `reference_frame`
#include "rosidl_runtime_c/string_functions.h"

bool
uc1_robot_perception__msg__Contact__init(uc1_robot_perception__msg__Contact * msg)
{
  if (!msg) {
    return false;
  }
  // contact_location
  if (!geometry_msgs__msg__Vector3__init(&msg->contact_location)) {
    uc1_robot_perception__msg__Contact__fini(msg);
    return false;
  }
  // contact_normal
  if (!geometry_msgs__msg__Vector3__init(&msg->contact_normal)) {
    uc1_robot_perception__msg__Contact__fini(msg);
    return false;
  }
  // contact_intensity
  // reference_frame
  if (!rosidl_runtime_c__String__init(&msg->reference_frame)) {
    uc1_robot_perception__msg__Contact__fini(msg);
    return false;
  }
  return true;
}

void
uc1_robot_perception__msg__Contact__fini(uc1_robot_perception__msg__Contact * msg)
{
  if (!msg) {
    return;
  }
  // contact_location
  geometry_msgs__msg__Vector3__fini(&msg->contact_location);
  // contact_normal
  geometry_msgs__msg__Vector3__fini(&msg->contact_normal);
  // contact_intensity
  // reference_frame
  rosidl_runtime_c__String__fini(&msg->reference_frame);
}

bool
uc1_robot_perception__msg__Contact__are_equal(const uc1_robot_perception__msg__Contact * lhs, const uc1_robot_perception__msg__Contact * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // contact_location
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->contact_location), &(rhs->contact_location)))
  {
    return false;
  }
  // contact_normal
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->contact_normal), &(rhs->contact_normal)))
  {
    return false;
  }
  // contact_intensity
  if (lhs->contact_intensity != rhs->contact_intensity) {
    return false;
  }
  // reference_frame
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->reference_frame), &(rhs->reference_frame)))
  {
    return false;
  }
  return true;
}

bool
uc1_robot_perception__msg__Contact__copy(
  const uc1_robot_perception__msg__Contact * input,
  uc1_robot_perception__msg__Contact * output)
{
  if (!input || !output) {
    return false;
  }
  // contact_location
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->contact_location), &(output->contact_location)))
  {
    return false;
  }
  // contact_normal
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->contact_normal), &(output->contact_normal)))
  {
    return false;
  }
  // contact_intensity
  output->contact_intensity = input->contact_intensity;
  // reference_frame
  if (!rosidl_runtime_c__String__copy(
      &(input->reference_frame), &(output->reference_frame)))
  {
    return false;
  }
  return true;
}

uc1_robot_perception__msg__Contact *
uc1_robot_perception__msg__Contact__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__Contact * msg = (uc1_robot_perception__msg__Contact *)allocator.allocate(sizeof(uc1_robot_perception__msg__Contact), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uc1_robot_perception__msg__Contact));
  bool success = uc1_robot_perception__msg__Contact__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uc1_robot_perception__msg__Contact__destroy(uc1_robot_perception__msg__Contact * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uc1_robot_perception__msg__Contact__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uc1_robot_perception__msg__Contact__Sequence__init(uc1_robot_perception__msg__Contact__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__Contact * data = NULL;

  if (size) {
    data = (uc1_robot_perception__msg__Contact *)allocator.zero_allocate(size, sizeof(uc1_robot_perception__msg__Contact), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uc1_robot_perception__msg__Contact__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uc1_robot_perception__msg__Contact__fini(&data[i - 1]);
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
uc1_robot_perception__msg__Contact__Sequence__fini(uc1_robot_perception__msg__Contact__Sequence * array)
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
      uc1_robot_perception__msg__Contact__fini(&array->data[i]);
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

uc1_robot_perception__msg__Contact__Sequence *
uc1_robot_perception__msg__Contact__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__Contact__Sequence * array = (uc1_robot_perception__msg__Contact__Sequence *)allocator.allocate(sizeof(uc1_robot_perception__msg__Contact__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uc1_robot_perception__msg__Contact__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uc1_robot_perception__msg__Contact__Sequence__destroy(uc1_robot_perception__msg__Contact__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uc1_robot_perception__msg__Contact__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uc1_robot_perception__msg__Contact__Sequence__are_equal(const uc1_robot_perception__msg__Contact__Sequence * lhs, const uc1_robot_perception__msg__Contact__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uc1_robot_perception__msg__Contact__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uc1_robot_perception__msg__Contact__Sequence__copy(
  const uc1_robot_perception__msg__Contact__Sequence * input,
  uc1_robot_perception__msg__Contact__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uc1_robot_perception__msg__Contact);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uc1_robot_perception__msg__Contact * data =
      (uc1_robot_perception__msg__Contact *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uc1_robot_perception__msg__Contact__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uc1_robot_perception__msg__Contact__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uc1_robot_perception__msg__Contact__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
