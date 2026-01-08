// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from uc1_robot_perception:msg/Contact.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__BUILDER_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "uc1_robot_perception/msg/detail/contact__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace uc1_robot_perception
{

namespace msg
{

namespace builder
{

class Init_Contact_reference_frame
{
public:
  explicit Init_Contact_reference_frame(::uc1_robot_perception::msg::Contact & msg)
  : msg_(msg)
  {}
  ::uc1_robot_perception::msg::Contact reference_frame(::uc1_robot_perception::msg::Contact::_reference_frame_type arg)
  {
    msg_.reference_frame = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_perception::msg::Contact msg_;
};

class Init_Contact_contact_intensity
{
public:
  explicit Init_Contact_contact_intensity(::uc1_robot_perception::msg::Contact & msg)
  : msg_(msg)
  {}
  Init_Contact_reference_frame contact_intensity(::uc1_robot_perception::msg::Contact::_contact_intensity_type arg)
  {
    msg_.contact_intensity = std::move(arg);
    return Init_Contact_reference_frame(msg_);
  }

private:
  ::uc1_robot_perception::msg::Contact msg_;
};

class Init_Contact_contact_normal
{
public:
  explicit Init_Contact_contact_normal(::uc1_robot_perception::msg::Contact & msg)
  : msg_(msg)
  {}
  Init_Contact_contact_intensity contact_normal(::uc1_robot_perception::msg::Contact::_contact_normal_type arg)
  {
    msg_.contact_normal = std::move(arg);
    return Init_Contact_contact_intensity(msg_);
  }

private:
  ::uc1_robot_perception::msg::Contact msg_;
};

class Init_Contact_contact_location
{
public:
  Init_Contact_contact_location()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Contact_contact_normal contact_location(::uc1_robot_perception::msg::Contact::_contact_location_type arg)
  {
    msg_.contact_location = std::move(arg);
    return Init_Contact_contact_normal(msg_);
  }

private:
  ::uc1_robot_perception::msg::Contact msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_perception::msg::Contact>()
{
  return uc1_robot_perception::msg::builder::Init_Contact_contact_location();
}

}  // namespace uc1_robot_perception

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__BUILDER_HPP_
