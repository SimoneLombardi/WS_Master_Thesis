// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotOrient.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_orient__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace uc1_robot_controllers_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void MoveRobotOrient_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) uc1_robot_controllers_interfaces::msg::MoveRobotOrient(_init);
}

void MoveRobotOrient_fini_function(void * message_memory)
{
  auto typed_message = static_cast<uc1_robot_controllers_interfaces::msg::MoveRobotOrient *>(message_memory);
  typed_message->~MoveRobotOrient();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MoveRobotOrient_message_member_array[3] = {
  {
    "roll",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_controllers_interfaces::msg::MoveRobotOrient, roll),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "pitch",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_controllers_interfaces::msg::MoveRobotOrient, pitch),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "yaw",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_controllers_interfaces::msg::MoveRobotOrient, yaw),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MoveRobotOrient_message_members = {
  "uc1_robot_controllers_interfaces::msg",  // message namespace
  "MoveRobotOrient",  // message name
  3,  // number of fields
  sizeof(uc1_robot_controllers_interfaces::msg::MoveRobotOrient),
  MoveRobotOrient_message_member_array,  // message members
  MoveRobotOrient_init_function,  // function to initialize message memory (memory has to be allocated)
  MoveRobotOrient_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MoveRobotOrient_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MoveRobotOrient_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace uc1_robot_controllers_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<uc1_robot_controllers_interfaces::msg::MoveRobotOrient>()
{
  return &::uc1_robot_controllers_interfaces::msg::rosidl_typesupport_introspection_cpp::MoveRobotOrient_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, uc1_robot_controllers_interfaces, msg, MoveRobotOrient)() {
  return &::uc1_robot_controllers_interfaces::msg::rosidl_typesupport_introspection_cpp::MoveRobotOrient_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
