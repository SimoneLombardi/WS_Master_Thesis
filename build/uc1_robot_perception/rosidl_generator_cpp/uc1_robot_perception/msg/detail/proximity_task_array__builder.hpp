// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from uc1_robot_perception:msg/ProximityTaskArray.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__BUILDER_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "uc1_robot_perception/msg/detail/proximity_task_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace uc1_robot_perception
{

namespace msg
{

namespace builder
{

class Init_ProximityTaskArray_proximity_tasks
{
public:
  Init_ProximityTaskArray_proximity_tasks()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::uc1_robot_perception::msg::ProximityTaskArray proximity_tasks(::uc1_robot_perception::msg::ProximityTaskArray::_proximity_tasks_type arg)
  {
    msg_.proximity_tasks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_perception::msg::ProximityTaskArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_perception::msg::ProximityTaskArray>()
{
  return uc1_robot_perception::msg::builder::Init_ProximityTaskArray_proximity_tasks();
}

}  // namespace uc1_robot_perception

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__BUILDER_HPP_
