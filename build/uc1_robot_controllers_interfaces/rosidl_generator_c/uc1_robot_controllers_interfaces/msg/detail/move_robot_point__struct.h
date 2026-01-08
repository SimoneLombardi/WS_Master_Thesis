// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotPoint.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_POINT__STRUCT_H_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_POINT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MoveRobotPoint in the package uc1_robot_controllers_interfaces.
/**
  * position of a point in space
 */
typedef struct uc1_robot_controllers_interfaces__msg__MoveRobotPoint
{
  double x;
  double y;
  double z;
} uc1_robot_controllers_interfaces__msg__MoveRobotPoint;

// Struct for a sequence of uc1_robot_controllers_interfaces__msg__MoveRobotPoint.
typedef struct uc1_robot_controllers_interfaces__msg__MoveRobotPoint__Sequence
{
  uc1_robot_controllers_interfaces__msg__MoveRobotPoint * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__msg__MoveRobotPoint__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_POINT__STRUCT_H_
