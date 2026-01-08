// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotGoal.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__STRUCT_H_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'translation'
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_point__struct.h"
// Member 'orientation'
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_orient__struct.h"

/// Struct defined in msg/MoveRobotGoal in the package uc1_robot_controllers_interfaces.
typedef struct uc1_robot_controllers_interfaces__msg__MoveRobotGoal
{
  uc1_robot_controllers_interfaces__msg__MoveRobotPoint translation;
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient orientation;
} uc1_robot_controllers_interfaces__msg__MoveRobotGoal;

// Struct for a sequence of uc1_robot_controllers_interfaces__msg__MoveRobotGoal.
typedef struct uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence
{
  uc1_robot_controllers_interfaces__msg__MoveRobotGoal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__STRUCT_H_
