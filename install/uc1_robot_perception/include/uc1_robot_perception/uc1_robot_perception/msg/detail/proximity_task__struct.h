// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uc1_robot_perception:msg/ProximityTask.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__STRUCT_H_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'min_point_robot'
// Member 'min_point_vector'
#include "geometry_msgs/msg/detail/vector3__struct.h"
// Member 'link_id'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ProximityTask in the package uc1_robot_perception.
typedef struct uc1_robot_perception__msg__ProximityTask
{
  geometry_msgs__msg__Vector3 min_point_robot;
  geometry_msgs__msg__Vector3 min_point_vector;
  float distance;
  rosidl_runtime_c__String link_id;
} uc1_robot_perception__msg__ProximityTask;

// Struct for a sequence of uc1_robot_perception__msg__ProximityTask.
typedef struct uc1_robot_perception__msg__ProximityTask__Sequence
{
  uc1_robot_perception__msg__ProximityTask * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_perception__msg__ProximityTask__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__STRUCT_H_
