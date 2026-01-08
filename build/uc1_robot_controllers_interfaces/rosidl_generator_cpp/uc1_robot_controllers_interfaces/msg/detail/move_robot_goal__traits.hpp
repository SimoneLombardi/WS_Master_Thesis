// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotGoal.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__TRAITS_HPP_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_goal__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'translation'
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_point__traits.hpp"
// Member 'orientation'
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_orient__traits.hpp"

namespace uc1_robot_controllers_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const MoveRobotGoal & msg,
  std::ostream & out)
{
  out << "{";
  // member: translation
  {
    out << "translation: ";
    to_flow_style_yaml(msg.translation, out);
    out << ", ";
  }

  // member: orientation
  {
    out << "orientation: ";
    to_flow_style_yaml(msg.orientation, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveRobotGoal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: translation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "translation:\n";
    to_block_style_yaml(msg.translation, out, indentation + 2);
  }

  // member: orientation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "orientation:\n";
    to_block_style_yaml(msg.orientation, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveRobotGoal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace uc1_robot_controllers_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use uc1_robot_controllers_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_robot_controllers_interfaces::msg::MoveRobotGoal & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_controllers_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_controllers_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_controllers_interfaces::msg::MoveRobotGoal & msg)
{
  return uc1_robot_controllers_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::msg::MoveRobotGoal>()
{
  return "uc1_robot_controllers_interfaces::msg::MoveRobotGoal";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::msg::MoveRobotGoal>()
{
  return "uc1_robot_controllers_interfaces/msg/MoveRobotGoal";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::msg::MoveRobotGoal>
  : std::integral_constant<bool, has_fixed_size<uc1_robot_controllers_interfaces::msg::MoveRobotOrient>::value && has_fixed_size<uc1_robot_controllers_interfaces::msg::MoveRobotPoint>::value> {};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::msg::MoveRobotGoal>
  : std::integral_constant<bool, has_bounded_size<uc1_robot_controllers_interfaces::msg::MoveRobotOrient>::value && has_bounded_size<uc1_robot_controllers_interfaces::msg::MoveRobotPoint>::value> {};

template<>
struct is_message<uc1_robot_controllers_interfaces::msg::MoveRobotGoal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__TRAITS_HPP_
