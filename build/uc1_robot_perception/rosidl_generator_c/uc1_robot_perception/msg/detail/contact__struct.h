// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uc1_robot_perception:msg/Contact.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__STRUCT_H_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'contact_location'
// Member 'contact_normal'
#include "geometry_msgs/msg/detail/vector3__struct.h"
// Member 'reference_frame'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Contact in the package uc1_robot_perception.
typedef struct uc1_robot_perception__msg__Contact
{
  geometry_msgs__msg__Vector3 contact_location;
  geometry_msgs__msg__Vector3 contact_normal;
  float contact_intensity;
  rosidl_runtime_c__String reference_frame;
} uc1_robot_perception__msg__Contact;

// Struct for a sequence of uc1_robot_perception__msg__Contact.
typedef struct uc1_robot_perception__msg__Contact__Sequence
{
  uc1_robot_perception__msg__Contact * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_perception__msg__Contact__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__STRUCT_H_
