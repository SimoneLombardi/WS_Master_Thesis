// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uc1_robot_perception:msg/ContactArray.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT_ARRAY__STRUCT_H_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'contacts'
#include "uc1_robot_perception/msg/detail/contact__struct.h"

/// Struct defined in msg/ContactArray in the package uc1_robot_perception.
typedef struct uc1_robot_perception__msg__ContactArray
{
  uc1_robot_perception__msg__Contact__Sequence contacts;
} uc1_robot_perception__msg__ContactArray;

// Struct for a sequence of uc1_robot_perception__msg__ContactArray.
typedef struct uc1_robot_perception__msg__ContactArray__Sequence
{
  uc1_robot_perception__msg__ContactArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_perception__msg__ContactArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT_ARRAY__STRUCT_H_
