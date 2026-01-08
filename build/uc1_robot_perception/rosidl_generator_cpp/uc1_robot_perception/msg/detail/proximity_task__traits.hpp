// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from uc1_robot_perception:msg/ProximityTask.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__TRAITS_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "uc1_robot_perception/msg/detail/proximity_task__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'min_point_robot'
// Member 'min_point_vector'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace uc1_robot_perception
{

namespace msg
{

inline void to_flow_style_yaml(
  const ProximityTask & msg,
  std::ostream & out)
{
  out << "{";
  // member: min_point_robot
  {
    out << "min_point_robot: ";
    to_flow_style_yaml(msg.min_point_robot, out);
    out << ", ";
  }

  // member: min_point_vector
  {
    out << "min_point_vector: ";
    to_flow_style_yaml(msg.min_point_vector, out);
    out << ", ";
  }

  // member: distance
  {
    out << "distance: ";
    rosidl_generator_traits::value_to_yaml(msg.distance, out);
    out << ", ";
  }

  // member: link_id
  {
    out << "link_id: ";
    rosidl_generator_traits::value_to_yaml(msg.link_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ProximityTask & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: min_point_robot
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "min_point_robot:\n";
    to_block_style_yaml(msg.min_point_robot, out, indentation + 2);
  }

  // member: min_point_vector
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "min_point_vector:\n";
    to_block_style_yaml(msg.min_point_vector, out, indentation + 2);
  }

  // member: distance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance: ";
    rosidl_generator_traits::value_to_yaml(msg.distance, out);
    out << "\n";
  }

  // member: link_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "link_id: ";
    rosidl_generator_traits::value_to_yaml(msg.link_id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ProximityTask & msg, bool use_flow_style = false)
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

}  // namespace uc1_robot_perception

namespace rosidl_generator_traits
{

[[deprecated("use uc1_robot_perception::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const uc1_robot_perception::msg::ProximityTask & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_perception::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_perception::msg::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_perception::msg::ProximityTask & msg)
{
  return uc1_robot_perception::msg::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_perception::msg::ProximityTask>()
{
  return "uc1_robot_perception::msg::ProximityTask";
}

template<>
inline const char * name<uc1_robot_perception::msg::ProximityTask>()
{
  return "uc1_robot_perception/msg/ProximityTask";
}

template<>
struct has_fixed_size<uc1_robot_perception::msg::ProximityTask>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<uc1_robot_perception::msg::ProximityTask>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<uc1_robot_perception::msg::ProximityTask>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__TRAITS_HPP_
