// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from uc1_robot_perception:msg/Contact.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__TRAITS_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "uc1_robot_perception/msg/detail/contact__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'contact_location'
// Member 'contact_normal'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace uc1_robot_perception
{

namespace msg
{

inline void to_flow_style_yaml(
  const Contact & msg,
  std::ostream & out)
{
  out << "{";
  // member: contact_location
  {
    out << "contact_location: ";
    to_flow_style_yaml(msg.contact_location, out);
    out << ", ";
  }

  // member: contact_normal
  {
    out << "contact_normal: ";
    to_flow_style_yaml(msg.contact_normal, out);
    out << ", ";
  }

  // member: contact_intensity
  {
    out << "contact_intensity: ";
    rosidl_generator_traits::value_to_yaml(msg.contact_intensity, out);
    out << ", ";
  }

  // member: reference_frame
  {
    out << "reference_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.reference_frame, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Contact & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: contact_location
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "contact_location:\n";
    to_block_style_yaml(msg.contact_location, out, indentation + 2);
  }

  // member: contact_normal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "contact_normal:\n";
    to_block_style_yaml(msg.contact_normal, out, indentation + 2);
  }

  // member: contact_intensity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "contact_intensity: ";
    rosidl_generator_traits::value_to_yaml(msg.contact_intensity, out);
    out << "\n";
  }

  // member: reference_frame
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reference_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.reference_frame, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Contact & msg, bool use_flow_style = false)
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
  const uc1_robot_perception::msg::Contact & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_perception::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_perception::msg::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_perception::msg::Contact & msg)
{
  return uc1_robot_perception::msg::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_perception::msg::Contact>()
{
  return "uc1_robot_perception::msg::Contact";
}

template<>
inline const char * name<uc1_robot_perception::msg::Contact>()
{
  return "uc1_robot_perception/msg/Contact";
}

template<>
struct has_fixed_size<uc1_robot_perception::msg::Contact>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<uc1_robot_perception::msg::Contact>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<uc1_robot_perception::msg::Contact>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__TRAITS_HPP_
