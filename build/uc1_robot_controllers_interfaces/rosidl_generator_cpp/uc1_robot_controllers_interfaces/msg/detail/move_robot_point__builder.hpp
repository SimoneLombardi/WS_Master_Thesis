// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotPoint.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_POINT__BUILDER_HPP_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_POINT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_point__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace uc1_robot_controllers_interfaces
{

namespace msg
{

namespace builder
{

class Init_MoveRobotPoint_z
{
public:
  explicit Init_MoveRobotPoint_z(::uc1_robot_controllers_interfaces::msg::MoveRobotPoint & msg)
  : msg_(msg)
  {}
  ::uc1_robot_controllers_interfaces::msg::MoveRobotPoint z(::uc1_robot_controllers_interfaces::msg::MoveRobotPoint::_z_type arg)
  {
    msg_.z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::msg::MoveRobotPoint msg_;
};

class Init_MoveRobotPoint_y
{
public:
  explicit Init_MoveRobotPoint_y(::uc1_robot_controllers_interfaces::msg::MoveRobotPoint & msg)
  : msg_(msg)
  {}
  Init_MoveRobotPoint_z y(::uc1_robot_controllers_interfaces::msg::MoveRobotPoint::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_MoveRobotPoint_z(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::msg::MoveRobotPoint msg_;
};

class Init_MoveRobotPoint_x
{
public:
  Init_MoveRobotPoint_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveRobotPoint_y x(::uc1_robot_controllers_interfaces::msg::MoveRobotPoint::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_MoveRobotPoint_y(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::msg::MoveRobotPoint msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::msg::MoveRobotPoint>()
{
  return uc1_robot_controllers_interfaces::msg::builder::Init_MoveRobotPoint_x();
}

}  // namespace uc1_robot_controllers_interfaces

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_POINT__BUILDER_HPP_
