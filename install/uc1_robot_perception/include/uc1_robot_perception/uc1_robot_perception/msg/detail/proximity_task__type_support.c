// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from uc1_robot_perception:msg/ProximityTask.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "uc1_robot_perception/msg/detail/proximity_task__rosidl_typesupport_introspection_c.h"
#include "uc1_robot_perception/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "uc1_robot_perception/msg/detail/proximity_task__functions.h"
#include "uc1_robot_perception/msg/detail/proximity_task__struct.h"


// Include directives for member types
// Member `min_point_robot`
// Member `min_point_vector`
#include "geometry_msgs/msg/vector3.h"
// Member `min_point_robot`
// Member `min_point_vector`
#include "geometry_msgs/msg/detail/vector3__rosidl_typesupport_introspection_c.h"
// Member `link_id`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  uc1_robot_perception__msg__ProximityTask__init(message_memory);
}

void uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_fini_function(void * message_memory)
{
  uc1_robot_perception__msg__ProximityTask__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_message_member_array[4] = {
  {
    "min_point_robot",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_perception__msg__ProximityTask, min_point_robot),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "min_point_vector",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_perception__msg__ProximityTask, min_point_vector),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "distance",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_perception__msg__ProximityTask, distance),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "link_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_perception__msg__ProximityTask, link_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_message_members = {
  "uc1_robot_perception__msg",  // message namespace
  "ProximityTask",  // message name
  4,  // number of fields
  sizeof(uc1_robot_perception__msg__ProximityTask),
  uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_message_member_array,  // message members
  uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_init_function,  // function to initialize message memory (memory has to be allocated)
  uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_message_type_support_handle = {
  0,
  &uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_uc1_robot_perception
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uc1_robot_perception, msg, ProximityTask)() {
  uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  if (!uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_message_type_support_handle.typesupport_identifier) {
    uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &uc1_robot_perception__msg__ProximityTask__rosidl_typesupport_introspection_c__ProximityTask_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
