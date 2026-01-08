// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotOrient.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_ORIENT__STRUCT_H_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_ORIENT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MoveRobotOrient in the package uc1_robot_controllers_interfaces.
/**
  * orientation of the robot in space (roll, pitch, yaw in radians)
 */
typedef struct uc1_robot_controllers_interfaces__msg__MoveRobotOrient
{
  double roll;
  double pitch;
  double yaw;
} uc1_robot_controllers_interfaces__msg__MoveRobotOrient;

// Struct for a sequence of uc1_robot_controllers_interfaces__msg__MoveRobotOrient.
typedef struct uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence
{
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__msg__MoveRobotOrient__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_ORIENT__STRUCT_H_
