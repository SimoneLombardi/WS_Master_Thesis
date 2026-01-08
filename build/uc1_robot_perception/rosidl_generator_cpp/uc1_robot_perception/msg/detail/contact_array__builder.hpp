// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from uc1_robot_perception:msg/ContactArray.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT_ARRAY__BUILDER_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "uc1_robot_perception/msg/detail/contact_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace uc1_robot_perception
{

namespace msg
{

namespace builder
{

class Init_ContactArray_contacts
{
public:
  Init_ContactArray_contacts()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::uc1_robot_perception::msg::ContactArray contacts(::uc1_robot_perception::msg::ContactArray::_contacts_type arg)
  {
    msg_.contacts = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_perception::msg::ContactArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_perception::msg::ContactArray>()
{
  return uc1_robot_perception::msg::builder::Init_ContactArray_contacts();
}

}  // namespace uc1_robot_perception

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT_ARRAY__BUILDER_HPP_
