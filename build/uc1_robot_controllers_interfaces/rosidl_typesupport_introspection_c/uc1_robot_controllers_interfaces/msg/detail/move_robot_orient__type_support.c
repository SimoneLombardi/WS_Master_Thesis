// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotOrient.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_orient__rosidl_typesupport_introspection_c.h"
#include "uc1_robot_controllers_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_orient__functions.h"
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_orient__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient__init(message_memory);
}

void uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_fini_function(void * message_memory)
{
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_message_member_array[3] = {
  {
    "roll",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_controllers_interfaces__msg__MoveRobotOrient, roll),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pitch",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_controllers_interfaces__msg__MoveRobotOrient, pitch),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yaw",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_controllers_interfaces__msg__MoveRobotOrient, yaw),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_message_members = {
  "uc1_robot_controllers_interfaces__msg",  // message namespace
  "MoveRobotOrient",  // message name
  3,  // number of fields
  sizeof(uc1_robot_controllers_interfaces__msg__MoveRobotOrient),
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_message_member_array,  // message members
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_init_function,  // function to initialize message memory (memory has to be allocated)
  uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_message_type_support_handle = {
  0,
  &uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_uc1_robot_controllers_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uc1_robot_controllers_interfaces, msg, MoveRobotOrient)() {
  if (!uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_message_type_support_handle.typesupport_identifier) {
    uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &uc1_robot_controllers_interfaces__msg__MoveRobotOrient__rosidl_typesupport_introspection_c__MoveRobotOrient_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
