// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from uc1_robot_perception:msg/ContactArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "uc1_robot_perception/msg/detail/contact_array__rosidl_typesupport_introspection_c.h"
#include "uc1_robot_perception/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "uc1_robot_perception/msg/detail/contact_array__functions.h"
#include "uc1_robot_perception/msg/detail/contact_array__struct.h"


// Include directives for member types
// Member `contacts`
#include "uc1_robot_perception/msg/contact.h"
// Member `contacts`
#include "uc1_robot_perception/msg/detail/contact__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  uc1_robot_perception__msg__ContactArray__init(message_memory);
}

void uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_fini_function(void * message_memory)
{
  uc1_robot_perception__msg__ContactArray__fini(message_memory);
}

size_t uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__size_function__ContactArray__contacts(
  const void * untyped_member)
{
  const uc1_robot_perception__msg__Contact__Sequence * member =
    (const uc1_robot_perception__msg__Contact__Sequence *)(untyped_member);
  return member->size;
}

const void * uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__get_const_function__ContactArray__contacts(
  const void * untyped_member, size_t index)
{
  const uc1_robot_perception__msg__Contact__Sequence * member =
    (const uc1_robot_perception__msg__Contact__Sequence *)(untyped_member);
  return &member->data[index];
}

void * uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__get_function__ContactArray__contacts(
  void * untyped_member, size_t index)
{
  uc1_robot_perception__msg__Contact__Sequence * member =
    (uc1_robot_perception__msg__Contact__Sequence *)(untyped_member);
  return &member->data[index];
}

void uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__fetch_function__ContactArray__contacts(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const uc1_robot_perception__msg__Contact * item =
    ((const uc1_robot_perception__msg__Contact *)
    uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__get_const_function__ContactArray__contacts(untyped_member, index));
  uc1_robot_perception__msg__Contact * value =
    (uc1_robot_perception__msg__Contact *)(untyped_value);
  *value = *item;
}

void uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__assign_function__ContactArray__contacts(
  void * untyped_member, size_t index, const void * untyped_value)
{
  uc1_robot_perception__msg__Contact * item =
    ((uc1_robot_perception__msg__Contact *)
    uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__get_function__ContactArray__contacts(untyped_member, index));
  const uc1_robot_perception__msg__Contact * value =
    (const uc1_robot_perception__msg__Contact *)(untyped_value);
  *item = *value;
}

bool uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__resize_function__ContactArray__contacts(
  void * untyped_member, size_t size)
{
  uc1_robot_perception__msg__Contact__Sequence * member =
    (uc1_robot_perception__msg__Contact__Sequence *)(untyped_member);
  uc1_robot_perception__msg__Contact__Sequence__fini(member);
  return uc1_robot_perception__msg__Contact__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_message_member_array[1] = {
  {
    "contacts",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(uc1_robot_perception__msg__ContactArray, contacts),  // bytes offset in struct
    NULL,  // default value
    uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__size_function__ContactArray__contacts,  // size() function pointer
    uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__get_const_function__ContactArray__contacts,  // get_const(index) function pointer
    uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__get_function__ContactArray__contacts,  // get(index) function pointer
    uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__fetch_function__ContactArray__contacts,  // fetch(index, &value) function pointer
    uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__assign_function__ContactArray__contacts,  // assign(index, value) function pointer
    uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__resize_function__ContactArray__contacts  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_message_members = {
  "uc1_robot_perception__msg",  // message namespace
  "ContactArray",  // message name
  1,  // number of fields
  sizeof(uc1_robot_perception__msg__ContactArray),
  uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_message_member_array,  // message members
  uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_init_function,  // function to initialize message memory (memory has to be allocated)
  uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_message_type_support_handle = {
  0,
  &uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_uc1_robot_perception
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uc1_robot_perception, msg, ContactArray)() {
  uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, uc1_robot_perception, msg, Contact)();
  if (!uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_message_type_support_handle.typesupport_identifier) {
    uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &uc1_robot_perception__msg__ContactArray__rosidl_typesupport_introspection_c__ContactArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
