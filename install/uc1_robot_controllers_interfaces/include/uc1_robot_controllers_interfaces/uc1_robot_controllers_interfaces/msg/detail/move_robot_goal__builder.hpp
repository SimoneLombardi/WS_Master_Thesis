// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotGoal.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__BUILDER_HPP_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_goal__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace uc1_robot_controllers_interfaces
{

namespace msg
{

namespace builder
{

class Init_MoveRobotGoal_orientation
{
public:
  explicit Init_MoveRobotGoal_orientation(::uc1_robot_controllers_interfaces::msg::MoveRobotGoal & msg)
  : msg_(msg)
  {}
  ::uc1_robot_controllers_interfaces::msg::MoveRobotGoal orientation(::uc1_robot_controllers_interfaces::msg::MoveRobotGoal::_orientation_type arg)
  {
    msg_.orientation = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::msg::MoveRobotGoal msg_;
};

class Init_MoveRobotGoal_translation
{
public:
  Init_MoveRobotGoal_translation()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveRobotGoal_orientation translation(::uc1_robot_controllers_interfaces::msg::MoveRobotGoal::_translation_type arg)
  {
    msg_.translation = std::move(arg);
    return Init_MoveRobotGoal_orientation(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::msg::MoveRobotGoal msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::msg::MoveRobotGoal>()
{
  return uc1_robot_controllers_interfaces::msg::builder::Init_MoveRobotGoal_translation();
}

}  // namespace uc1_robot_controllers_interfaces

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__BUILDER_HPP_
