// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from uc1_robot_controllers_interfaces:action/MoveRobotTP.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT_TP__STRUCT_H_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT_TP__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'goal'
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_goal__struct.h"
// Member 'init_config_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/MoveRobotTP in the package uc1_robot_controllers_interfaces.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal
{
  uc1_robot_controllers_interfaces__msg__MoveRobotGoal goal;
  rosidl_runtime_c__String init_config_name;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal;

// Struct for a sequence of uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal__Sequence
{
  uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/MoveRobotTP in the package uc1_robot_controllers_interfaces.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_Result
{
  rosidl_runtime_c__String result;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_Result;

// Struct for a sequence of uc1_robot_controllers_interfaces__action__MoveRobotTP_Result.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_Result__Sequence
{
  uc1_robot_controllers_interfaces__action__MoveRobotTP_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_Result__Sequence;


// Constants defined in the message

/// Struct defined in action/MoveRobotTP in the package uc1_robot_controllers_interfaces.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback
{
  double linvel_norm;
  double angvel_norm;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback;

// Struct for a sequence of uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback__Sequence
{
  uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "uc1_robot_controllers_interfaces/action/detail/move_robot_tp__struct.h"

/// Struct defined in action/MoveRobotTP in the package uc1_robot_controllers_interfaces.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal goal;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Request;

// Struct for a sequence of uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Request.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Request__Sequence
{
  uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/MoveRobotTP in the package uc1_robot_controllers_interfaces.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Response;

// Struct for a sequence of uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Response.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Response__Sequence
{
  uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/MoveRobotTP in the package uc1_robot_controllers_interfaces.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Request;

// Struct for a sequence of uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Request.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Request__Sequence
{
  uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "uc1_robot_controllers_interfaces/action/detail/move_robot_tp__struct.h"

/// Struct defined in action/MoveRobotTP in the package uc1_robot_controllers_interfaces.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Response
{
  int8_t status;
  uc1_robot_controllers_interfaces__action__MoveRobotTP_Result result;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Response;

// Struct for a sequence of uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Response.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Response__Sequence
{
  uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "uc1_robot_controllers_interfaces/action/detail/move_robot_tp__struct.h"

/// Struct defined in action/MoveRobotTP in the package uc1_robot_controllers_interfaces.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback feedback;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_FeedbackMessage;

// Struct for a sequence of uc1_robot_controllers_interfaces__action__MoveRobotTP_FeedbackMessage.
typedef struct uc1_robot_controllers_interfaces__action__MoveRobotTP_FeedbackMessage__Sequence
{
  uc1_robot_controllers_interfaces__action__MoveRobotTP_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} uc1_robot_controllers_interfaces__action__MoveRobotTP_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT_TP__STRUCT_H_
