// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotGoal.idl
// generated code does not contain a copyright notice
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_goal__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "uc1_robot_controllers_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_goal__struct.h"
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_goal__functions.h"
#include "fastcdr/Cdr.h"

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

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_orient__functions.h"  // orientation
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_point__functions.h"  // translation

// forward declare type support functions
size_t get_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotOrient(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotOrient(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, uc1_robot_controllers_interfaces, msg, MoveRobotOrient)();
size_t get_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotPoint(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotPoint(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, uc1_robot_controllers_interfaces, msg, MoveRobotPoint)();


using _MoveRobotGoal__ros_msg_type = uc1_robot_controllers_interfaces__msg__MoveRobotGoal;

static bool _MoveRobotGoal__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _MoveRobotGoal__ros_msg_type * ros_message = static_cast<const _MoveRobotGoal__ros_msg_type *>(untyped_ros_message);
  // Field name: translation
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, uc1_robot_controllers_interfaces, msg, MoveRobotPoint
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->translation, cdr))
    {
      return false;
    }
  }

  // Field name: orientation
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, uc1_robot_controllers_interfaces, msg, MoveRobotOrient
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->orientation, cdr))
    {
      return false;
    }
  }

  return true;
}

static bool _MoveRobotGoal__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _MoveRobotGoal__ros_msg_type * ros_message = static_cast<_MoveRobotGoal__ros_msg_type *>(untyped_ros_message);
  // Field name: translation
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, uc1_robot_controllers_interfaces, msg, MoveRobotPoint
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->translation))
    {
      return false;
    }
  }

  // Field name: orientation
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, uc1_robot_controllers_interfaces, msg, MoveRobotOrient
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->orientation))
    {
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_uc1_robot_controllers_interfaces
size_t get_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotGoal(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _MoveRobotGoal__ros_msg_type * ros_message = static_cast<const _MoveRobotGoal__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name translation

  current_alignment += get_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotPoint(
    &(ros_message->translation), current_alignment);
  // field.name orientation

  current_alignment += get_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotOrient(
    &(ros_message->orientation), current_alignment);

  return current_alignment - initial_alignment;
}

static uint32_t _MoveRobotGoal__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotGoal(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_uc1_robot_controllers_interfaces
size_t max_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotGoal(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: translation
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotPoint(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }
  // member: orientation
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotOrient(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = uc1_robot_controllers_interfaces__msg__MoveRobotGoal;
    is_plain =
      (
      offsetof(DataType, orientation) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _MoveRobotGoal__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_uc1_robot_controllers_interfaces__msg__MoveRobotGoal(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_MoveRobotGoal = {
  "uc1_robot_controllers_interfaces::msg",
  "MoveRobotGoal",
  _MoveRobotGoal__cdr_serialize,
  _MoveRobotGoal__cdr_deserialize,
  _MoveRobotGoal__get_serialized_size,
  _MoveRobotGoal__max_serialized_size
};

static rosidl_message_type_support_t _MoveRobotGoal__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_MoveRobotGoal,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, uc1_robot_controllers_interfaces, msg, MoveRobotGoal)() {
  return &_MoveRobotGoal__type_support;
}

#if defined(__cplusplus)
}
#endif
