// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotGoal.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "uc1_robot_controllers_interfaces/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_goal__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace uc1_robot_controllers_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_uc1_robot_controllers_interfaces
cdr_serialize(
  const uc1_robot_controllers_interfaces::msg::MoveRobotGoal & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_uc1_robot_controllers_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  uc1_robot_controllers_interfaces::msg::MoveRobotGoal & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_uc1_robot_controllers_interfaces
get_serialized_size(
  const uc1_robot_controllers_interfaces::msg::MoveRobotGoal & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_uc1_robot_controllers_interfaces
max_serialized_size_MoveRobotGoal(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace uc1_robot_controllers_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_uc1_robot_controllers_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, uc1_robot_controllers_interfaces, msg, MoveRobotGoal)();

#ifdef __cplusplus
}
#endif

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
