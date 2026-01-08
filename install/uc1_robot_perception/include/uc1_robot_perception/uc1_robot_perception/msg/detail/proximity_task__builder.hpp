// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from uc1_robot_perception:msg/ProximityTask.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__BUILDER_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "uc1_robot_perception/msg/detail/proximity_task__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace uc1_robot_perception
{

namespace msg
{

namespace builder
{

class Init_ProximityTask_link_id
{
public:
  explicit Init_ProximityTask_link_id(::uc1_robot_perception::msg::ProximityTask & msg)
  : msg_(msg)
  {}
  ::uc1_robot_perception::msg::ProximityTask link_id(::uc1_robot_perception::msg::ProximityTask::_link_id_type arg)
  {
    msg_.link_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_perception::msg::ProximityTask msg_;
};

class Init_ProximityTask_distance
{
public:
  explicit Init_ProximityTask_distance(::uc1_robot_perception::msg::ProximityTask & msg)
  : msg_(msg)
  {}
  Init_ProximityTask_link_id distance(::uc1_robot_perception::msg::ProximityTask::_distance_type arg)
  {
    msg_.distance = std::move(arg);
    return Init_ProximityTask_link_id(msg_);
  }

private:
  ::uc1_robot_perception::msg::ProximityTask msg_;
};

class Init_ProximityTask_min_point_vector
{
public:
  explicit Init_ProximityTask_min_point_vector(::uc1_robot_perception::msg::ProximityTask & msg)
  : msg_(msg)
  {}
  Init_ProximityTask_distance min_point_vector(::uc1_robot_perception::msg::ProximityTask::_min_point_vector_type arg)
  {
    msg_.min_point_vector = std::move(arg);
    return Init_ProximityTask_distance(msg_);
  }

private:
  ::uc1_robot_perception::msg::ProximityTask msg_;
};

class Init_ProximityTask_min_point_robot
{
public:
  Init_ProximityTask_min_point_robot()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ProximityTask_min_point_vector min_point_robot(::uc1_robot_perception::msg::ProximityTask::_min_point_robot_type arg)
  {
    msg_.min_point_robot = std::move(arg);
    return Init_ProximityTask_min_point_vector(msg_);
  }

private:
  ::uc1_robot_perception::msg::ProximityTask msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_perception::msg::ProximityTask>()
{
  return uc1_robot_perception::msg::builder::Init_ProximityTask_min_point_robot();
}

}  // namespace uc1_robot_perception

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__BUILDER_HPP_
