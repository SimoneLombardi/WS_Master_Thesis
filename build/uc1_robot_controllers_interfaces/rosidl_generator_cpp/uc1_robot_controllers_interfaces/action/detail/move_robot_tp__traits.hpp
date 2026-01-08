// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from uc1_robot_controllers_interfaces:action/MoveRobotTP.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT_TP__TRAITS_HPP_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT_TP__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "uc1_robot_controllers_interfaces/action/detail/move_robot_tp__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'goal'
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_goal__traits.hpp"

namespace uc1_robot_controllers_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveRobotTP_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
    out << ", ";
  }

  // member: init_config_name
  {
    out << "init_config_name: ";
    rosidl_generator_traits::value_to_yaml(msg.init_config_name, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveRobotTP_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }

  // member: init_config_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "init_config_name: ";
    rosidl_generator_traits::value_to_yaml(msg.init_config_name, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveRobotTP_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use uc1_robot_controllers_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_controllers_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_controllers_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal & msg)
{
  return uc1_robot_controllers_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal>()
{
  return "uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal>()
{
  return "uc1_robot_controllers_interfaces/action/MoveRobotTP_Goal";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace uc1_robot_controllers_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveRobotTP_Result & msg,
  std::ostream & out)
{
  out << "{";
  // member: result
  {
    out << "result: ";
    rosidl_generator_traits::value_to_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveRobotTP_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result: ";
    rosidl_generator_traits::value_to_yaml(msg.result, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveRobotTP_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use uc1_robot_controllers_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_robot_controllers_interfaces::action::MoveRobotTP_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_controllers_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_controllers_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_controllers_interfaces::action::MoveRobotTP_Result & msg)
{
  return uc1_robot_controllers_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result>()
{
  return "uc1_robot_controllers_interfaces::action::MoveRobotTP_Result";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result>()
{
  return "uc1_robot_controllers_interfaces/action/MoveRobotTP_Result";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace uc1_robot_controllers_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveRobotTP_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: linvel_norm
  {
    out << "linvel_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.linvel_norm, out);
    out << ", ";
  }

  // member: angvel_norm
  {
    out << "angvel_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.angvel_norm, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveRobotTP_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: linvel_norm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "linvel_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.linvel_norm, out);
    out << "\n";
  }

  // member: angvel_norm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angvel_norm: ";
    rosidl_generator_traits::value_to_yaml(msg.angvel_norm, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveRobotTP_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use uc1_robot_controllers_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_controllers_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_controllers_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback & msg)
{
  return uc1_robot_controllers_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback>()
{
  return "uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback>()
{
  return "uc1_robot_controllers_interfaces/action/MoveRobotTP_Feedback";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "uc1_robot_controllers_interfaces/action/detail/move_robot_tp__traits.hpp"

namespace uc1_robot_controllers_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveRobotTP_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveRobotTP_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveRobotTP_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use uc1_robot_controllers_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_controllers_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_controllers_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request & msg)
{
  return uc1_robot_controllers_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request>()
{
  return "uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request>()
{
  return "uc1_robot_controllers_interfaces/action/MoveRobotTP_SendGoal_Request";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace uc1_robot_controllers_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveRobotTP_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveRobotTP_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveRobotTP_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use uc1_robot_controllers_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_controllers_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_controllers_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response & msg)
{
  return uc1_robot_controllers_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response>()
{
  return "uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response>()
{
  return "uc1_robot_controllers_interfaces/action/MoveRobotTP_SendGoal_Response";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal>()
{
  return "uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal>()
{
  return "uc1_robot_controllers_interfaces/action/MoveRobotTP_SendGoal";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request>::value &&
    has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request>::value &&
    has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace uc1_robot_controllers_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveRobotTP_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveRobotTP_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveRobotTP_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use uc1_robot_controllers_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_controllers_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_controllers_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request & msg)
{
  return uc1_robot_controllers_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request>()
{
  return "uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request>()
{
  return "uc1_robot_controllers_interfaces/action/MoveRobotTP_GetResult_Request";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "uc1_robot_controllers_interfaces/action/detail/move_robot_tp__traits.hpp"

namespace uc1_robot_controllers_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveRobotTP_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveRobotTP_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveRobotTP_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use uc1_robot_controllers_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_controllers_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_controllers_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response & msg)
{
  return uc1_robot_controllers_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response>()
{
  return "uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response>()
{
  return "uc1_robot_controllers_interfaces/action/MoveRobotTP_GetResult_Response";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result>::value> {};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result>::value> {};

template<>
struct is_message<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult>()
{
  return "uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult>()
{
  return "uc1_robot_controllers_interfaces/action/MoveRobotTP_GetResult";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request>::value &&
    has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request>::value &&
    has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response>::value
  >
{
};

template<>
struct is_service<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "uc1_robot_controllers_interfaces/action/detail/move_robot_tp__traits.hpp"

namespace uc1_robot_controllers_interfaces
{

namespace action
{

inline void to_flow_style_yaml(
  const MoveRobotTP_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveRobotTP_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveRobotTP_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use uc1_robot_controllers_interfaces::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_controllers_interfaces::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_controllers_interfaces::action::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage & msg)
{
  return uc1_robot_controllers_interfaces::action::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage>()
{
  return "uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage>()
{
  return "uc1_robot_controllers_interfaces/action/MoveRobotTP_FeedbackMessage";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<uc1_robot_controllers_interfaces::action::MoveRobotTP>
  : std::true_type
{
};

template<>
struct is_action_goal<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT_TP__TRAITS_HPP_
