// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uc1_robot_perception:msg/ProximityTaskArray.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__STRUCT_H_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'proximity_tasks'
#include "uc1_robot_perception/msg/detail/proximity_task__struct.h"

/// Struct defined in msg/ProximityTaskArray in the package uc1_robot_perception.
typedef struct uc1_robot_perception__msg__ProximityTaskArray
{
  uc1_robot_perception__msg__ProximityTask__Sequence proximity_tasks;
} uc1_robot_perception__msg__ProximityTaskArray;

// Struct for a sequence of uc1_robot_perception__msg__ProximityTaskArray.
typedef struct uc1_robot_perception__msg__ProximityTaskArray__Sequence
{
  uc1_robot_perception__msg__ProximityTaskArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_perception__msg__ProximityTaskArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__STRUCT_H_
