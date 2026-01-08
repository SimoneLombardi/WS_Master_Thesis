// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotOrient.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_ORIENT__BUILDER_HPP_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_ORIENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_orient__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace uc1_robot_controllers_interfaces
{

namespace msg
{

namespace builder
{

class Init_MoveRobotOrient_yaw
{
public:
  explicit Init_MoveRobotOrient_yaw(::uc1_robot_controllers_interfaces::msg::MoveRobotOrient & msg)
  : msg_(msg)
  {}
  ::uc1_robot_controllers_interfaces::msg::MoveRobotOrient yaw(::uc1_robot_controllers_interfaces::msg::MoveRobotOrient::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::msg::MoveRobotOrient msg_;
};

class Init_MoveRobotOrient_pitch
{
public:
  explicit Init_MoveRobotOrient_pitch(::uc1_robot_controllers_interfaces::msg::MoveRobotOrient & msg)
  : msg_(msg)
  {}
  Init_MoveRobotOrient_yaw pitch(::uc1_robot_controllers_interfaces::msg::MoveRobotOrient::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_MoveRobotOrient_yaw(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::msg::MoveRobotOrient msg_;
};

class Init_MoveRobotOrient_roll
{
public:
  Init_MoveRobotOrient_roll()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveRobotOrient_pitch roll(::uc1_robot_controllers_interfaces::msg::MoveRobotOrient::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_MoveRobotOrient_pitch(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::msg::MoveRobotOrient msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::msg::MoveRobotOrient>()
{
  return uc1_robot_controllers_interfaces::msg::builder::Init_MoveRobotOrient_roll();
}

}  // namespace uc1_robot_controllers_interfaces

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_ORIENT__BUILDER_HPP_
