// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotPoint.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_POINT__TRAITS_HPP_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_POINT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_point__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace uc1_robot_controllers_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const MoveRobotPoint & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MoveRobotPoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MoveRobotPoint & msg, bool use_flow_style = false)
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
  const uc1_robot_controllers_interfaces::msg::MoveRobotPoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_controllers_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_controllers_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_controllers_interfaces::msg::MoveRobotPoint & msg)
{
  return uc1_robot_controllers_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_controllers_interfaces::msg::MoveRobotPoint>()
{
  return "uc1_robot_controllers_interfaces::msg::MoveRobotPoint";
}

template<>
inline const char * name<uc1_robot_controllers_interfaces::msg::MoveRobotPoint>()
{
  return "uc1_robot_controllers_interfaces/msg/MoveRobotPoint";
}

template<>
struct has_fixed_size<uc1_robot_controllers_interfaces::msg::MoveRobotPoint>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<uc1_robot_controllers_interfaces::msg::MoveRobotPoint>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<uc1_robot_controllers_interfaces::msg::MoveRobotPoint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_POINT__TRAITS_HPP_
