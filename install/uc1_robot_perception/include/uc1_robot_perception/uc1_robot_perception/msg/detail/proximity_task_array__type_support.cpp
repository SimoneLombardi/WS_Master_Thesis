// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from uc1_robot_perception:msg/ProximityTaskArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "uc1_robot_perception/msg/detail/proximity_task_array__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace uc1_robot_perception
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ProximityTaskArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) uc1_robot_perception::msg::ProximityTaskArray(_init);
}

void ProximityTaskArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<uc1_robot_perception::msg::ProximityTaskArray *>(message_memory);
  typed_message->~ProximityTaskArray();
}

size_t size_function__ProximityTaskArray__proximity_tasks(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<uc1_robot_perception::msg::ProximityTask> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ProximityTaskArray__proximity_tasks(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<uc1_robot_perception::msg::ProximityTask> *>(untyped_member);
  return &member[index];
}

void * get_function__ProximityTaskArray__proximity_tasks(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<uc1_robot_perception::msg::ProximityTask> *>(untyped_member);
  return &member[index];
}

void fetch_function__ProximityTaskArray__proximity_tasks(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const uc1_robot_perception::msg::ProximityTask *>(
    get_const_function__ProximityTaskArray__proximity_tasks(untyped_member, index));
  auto & value = *reinterpret_cast<uc1_robot_perception::msg::ProximityTask *>(untyped_value);
  value = item;
}

void assign_function__ProximityTaskArray__proximity_tasks(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<uc1_robot_perception::msg::ProximityTask *>(
    get_function__ProximityTaskArray__proximity_tasks(untyped_member, index));
  const auto & value = *reinterpret_cast<const uc1_robot_perception::msg::ProximityTask *>(untyped_value);
  item = value;
}

void resize_function__ProximityTaskArray__proximity_tasks(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<uc1_robot_perception::msg::ProximityTask> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ProximityTaskArray_message_member_array[1] = {
  {
    "proximity_tasks",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<uc1_robot_perception::msg::ProximityTask>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_perception::msg::ProximityTaskArray, proximity_tasks),  // bytes offset in struct
    nullptr,  // default value
    size_function__ProximityTaskArray__proximity_tasks,  // size() function pointer
    get_const_function__ProximityTaskArray__proximity_tasks,  // get_const(index) function pointer
    get_function__ProximityTaskArray__proximity_tasks,  // get(index) function pointer
    fetch_function__ProximityTaskArray__proximity_tasks,  // fetch(index, &value) function pointer
    assign_function__ProximityTaskArray__proximity_tasks,  // assign(index, value) function pointer
    resize_function__ProximityTaskArray__proximity_tasks  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ProximityTaskArray_message_members = {
  "uc1_robot_perception::msg",  // message namespace
  "ProximityTaskArray",  // message name
  1,  // number of fields
  sizeof(uc1_robot_perception::msg::ProximityTaskArray),
  ProximityTaskArray_message_member_array,  // message members
  ProximityTaskArray_init_function,  // function to initialize message memory (memory has to be allocated)
  ProximityTaskArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ProximityTaskArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ProximityTaskArray_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace uc1_robot_perception


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<uc1_robot_perception::msg::ProximityTaskArray>()
{
  return &::uc1_robot_perception::msg::rosidl_typesupport_introspection_cpp::ProximityTaskArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, uc1_robot_perception, msg, ProximityTaskArray)() {
  return &::uc1_robot_perception::msg::rosidl_typesupport_introspection_cpp::ProximityTaskArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
