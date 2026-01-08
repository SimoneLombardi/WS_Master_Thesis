// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from uc1_robot_perception:msg/ContactArray.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT_ARRAY__TRAITS_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "uc1_robot_perception/msg/detail/contact_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'contacts'
#include "uc1_robot_perception/msg/detail/contact__traits.hpp"

namespace uc1_robot_perception
{

namespace msg
{

inline void to_flow_style_yaml(
  const ContactArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: contacts
  {
    if (msg.contacts.size() == 0) {
      out << "contacts: []";
    } else {
      out << "contacts: [";
      size_t pending_items = msg.contacts.size();
      for (auto item : msg.contacts) {
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
  const ContactArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: contacts
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.contacts.size() == 0) {
      out << "contacts: []\n";
    } else {
      out << "contacts:\n";
      for (auto item : msg.contacts) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ContactArray & msg, bool use_flow_style = false)
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
  const uc1_robot_perception::msg::ContactArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  uc1_robot_perception::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use uc1_robot_perception::msg::to_yaml() instead")]]
inline std::string to_yaml(const uc1_robot_perception::msg::ContactArray & msg)
{
  return uc1_robot_perception::msg::to_yaml(msg);
}

template<>
inline const char * data_type<uc1_robot_perception::msg::ContactArray>()
{
  return "uc1_robot_perception::msg::ContactArray";
}

template<>
inline const char * name<uc1_robot_perception::msg::ContactArray>()
{
  return "uc1_robot_perception/msg/ContactArray";
}

template<>
struct has_fixed_size<uc1_robot_perception::msg::ContactArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<uc1_robot_perception::msg::ContactArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<uc1_robot_perception::msg::ContactArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT_ARRAY__TRAITS_HPP_
