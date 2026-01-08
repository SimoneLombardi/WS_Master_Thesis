// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotGoal.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__FUNCTIONS_H_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "uc1_robot_controllers_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_goal__struct.h"

/// Initialize msg/MoveRobotGoal message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * uc1_robot_controllers_interfaces__msg__MoveRobotGoal
 * )) before or use
 * uc1_robot_controllers_interfaces__msg__MoveRobotGoal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
bool
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__init(uc1_robot_controllers_interfaces__msg__MoveRobotGoal * msg);

/// Finalize msg/MoveRobotGoal message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
void
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__fini(uc1_robot_controllers_interfaces__msg__MoveRobotGoal * msg);

/// Create msg/MoveRobotGoal message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * uc1_robot_controllers_interfaces__msg__MoveRobotGoal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
uc1_robot_controllers_interfaces__msg__MoveRobotGoal *
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__create();

/// Destroy msg/MoveRobotGoal message.
/**
 * It calls
 * uc1_robot_controllers_interfaces__msg__MoveRobotGoal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
void
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__destroy(uc1_robot_controllers_interfaces__msg__MoveRobotGoal * msg);

/// Check for msg/MoveRobotGoal message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
bool
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__are_equal(const uc1_robot_controllers_interfaces__msg__MoveRobotGoal * lhs, const uc1_robot_controllers_interfaces__msg__MoveRobotGoal * rhs);

/// Copy a msg/MoveRobotGoal message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
bool
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__copy(
  const uc1_robot_controllers_interfaces__msg__MoveRobotGoal * input,
  uc1_robot_controllers_interfaces__msg__MoveRobotGoal * output);

/// Initialize array of msg/MoveRobotGoal messages.
/**
 * It allocates the memory for the number of elements and calls
 * uc1_robot_controllers_interfaces__msg__MoveRobotGoal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
bool
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence__init(uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence * array, size_t size);

/// Finalize array of msg/MoveRobotGoal messages.
/**
 * It calls
 * uc1_robot_controllers_interfaces__msg__MoveRobotGoal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
void
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence__fini(uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence * array);

/// Create array of msg/MoveRobotGoal messages.
/**
 * It allocates the memory for the array and calls
 * uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence *
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence__create(size_t size);

/// Destroy array of msg/MoveRobotGoal messages.
/**
 * It calls
 * uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
void
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence__destroy(uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence * array);

/// Check for msg/MoveRobotGoal message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
bool
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence__are_equal(const uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence * lhs, const uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence * rhs);

/// Copy an array of msg/MoveRobotGoal messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_uc1_robot_controllers_interfaces
bool
uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence__copy(
  const uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence * input,
  uc1_robot_controllers_interfaces__msg__MoveRobotGoal__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__FUNCTIONS_H_
