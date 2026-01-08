// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from uc1_robot_perception:msg/ContactArray.idl
// generated code does not contain a copyright notice
#include "uc1_robot_perception/msg/detail/contact_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `contacts`
#include "uc1_robot_perception/msg/detail/contact__functions.h"

bool
uc1_robot_perception__msg__ContactArray__init(uc1_robot_perception__msg__ContactArray * msg)
{
  if (!msg) {
    return false;
  }
  // contacts
  if (!uc1_robot_perception__msg__Contact__Sequence__init(&msg->contacts, 0)) {
    uc1_robot_perception__msg__ContactArray__fini(msg);
    return false;
  }
  return true;
}

void
uc1_robot_perception__msg__ContactArray__fini(uc1_robot_perception__msg__ContactArray * msg)
{
  if (!msg) {
    return;
  }
  // contacts
  uc1_robot_perception__msg__Contact__Sequence__fini(&msg->contacts);
}

bool
uc1_robot_perception__msg__ContactArray__are_equal(const uc1_robot_perception__msg__ContactArray * lhs, const uc1_robot_perception__msg__ContactArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // contacts
  if (!uc1_robot_perception__msg__Contact__Sequence__are_equal(
      &(lhs->contacts), &(rhs->contacts)))
  {
    return false;
  }
  return true;
}

bool
uc1_robot_perception__msg__ContactArray__copy(
  const uc1_robot_perception__msg__ContactArray * input,
  uc1_robot_perception__msg__ContactArray * output)
{
  if (!input || !output) {
    return false;
  }
  // contacts
  if (!uc1_robot_perception__msg__Contact__Sequence__copy(
      &(input->contacts), &(output->contacts)))
  {
    return false;
  }
  return true;
}

uc1_robot_perception__msg__ContactArray *
uc1_robot_perception__msg__ContactArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__ContactArray * msg = (uc1_robot_perception__msg__ContactArray *)allocator.allocate(sizeof(uc1_robot_perception__msg__ContactArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(uc1_robot_perception__msg__ContactArray));
  bool success = uc1_robot_perception__msg__ContactArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
uc1_robot_perception__msg__ContactArray__destroy(uc1_robot_perception__msg__ContactArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    uc1_robot_perception__msg__ContactArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
uc1_robot_perception__msg__ContactArray__Sequence__init(uc1_robot_perception__msg__ContactArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__ContactArray * data = NULL;

  if (size) {
    data = (uc1_robot_perception__msg__ContactArray *)allocator.zero_allocate(size, sizeof(uc1_robot_perception__msg__ContactArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = uc1_robot_perception__msg__ContactArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        uc1_robot_perception__msg__ContactArray__fini(&data[i - 1]);
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
uc1_robot_perception__msg__ContactArray__Sequence__fini(uc1_robot_perception__msg__ContactArray__Sequence * array)
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
      uc1_robot_perception__msg__ContactArray__fini(&array->data[i]);
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

uc1_robot_perception__msg__ContactArray__Sequence *
uc1_robot_perception__msg__ContactArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  uc1_robot_perception__msg__ContactArray__Sequence * array = (uc1_robot_perception__msg__ContactArray__Sequence *)allocator.allocate(sizeof(uc1_robot_perception__msg__ContactArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = uc1_robot_perception__msg__ContactArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
uc1_robot_perception__msg__ContactArray__Sequence__destroy(uc1_robot_perception__msg__ContactArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    uc1_robot_perception__msg__ContactArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
uc1_robot_perception__msg__ContactArray__Sequence__are_equal(const uc1_robot_perception__msg__ContactArray__Sequence * lhs, const uc1_robot_perception__msg__ContactArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!uc1_robot_perception__msg__ContactArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
uc1_robot_perception__msg__ContactArray__Sequence__copy(
  const uc1_robot_perception__msg__ContactArray__Sequence * input,
  uc1_robot_perception__msg__ContactArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(uc1_robot_perception__msg__ContactArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    uc1_robot_perception__msg__ContactArray * data =
      (uc1_robot_perception__msg__ContactArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!uc1_robot_perception__msg__ContactArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          uc1_robot_perception__msg__ContactArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!uc1_robot_perception__msg__ContactArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
