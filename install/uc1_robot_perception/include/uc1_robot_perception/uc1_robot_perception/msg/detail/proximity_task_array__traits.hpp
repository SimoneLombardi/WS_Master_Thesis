// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from uc1_robot_perception:msg/ProximityTaskArray.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__TRAITS_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "uc1_robot_perception/msg/detail/proximity_task_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'proximity_tasks'
#include "uc1_robot_perception/msg/detail/proximity_task__traits.hpp"

namespace uc1_robot_perception
{

namespace msg
{

inline void to_flow_style_yaml(
  const ProximityTaskArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: proximity_tasks
  {
    if (msg.proximity_tasks.size() == 0) {
      out << "proximity_tasks: []";
    } else {
      out << "proximity_tasks: [";
      size_t pending_items = msg.proximity_tasks.size();
      for (auto item : msg.proximity_tasks) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ProximityTaskArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: proximity_tasks
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.proximity_tasks.size() == 0) {
      out << "proximity_tasks: []\n";
    } else {
      out << "proximity_tasks:\n";
      for (auto item : msg.proximity_tasks) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ProximityTaskArray & msg, bool use_flow_style = false)
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
  const uc1_robot_perception::msg::ProximityTaskArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_perception::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_perception::msg::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_perception::msg::ProximityTaskArray & msg)
{
  return uc1_robot_perception::msg::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_perception::msg::ProximityTaskArray>()
{
  return "uc1_robot_perception::msg::ProximityTaskArray";
}

template<>
inline const char * name<uc1_robot_perception::msg::ProximityTaskArray>()
{
  return "uc1_robot_perception/msg/ProximityTaskArray";
}

template<>
struct has_fixed_size<uc1_robot_perception::msg::ProximityTaskArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<uc1_robot_perception::msg::ProximityTaskArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<uc1_robot_perception::msg::ProximityTaskArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__TRAITS_HPP_
