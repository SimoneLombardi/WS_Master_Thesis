// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from uc1_robot_perception:msg/ProximityTask.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__STRUCT_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'min_point_robot'
// Member 'min_point_vector'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_robot_perception__msg__ProximityTask __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_perception__msg__ProximityTask __declspec(deprecated)
#endif

namespace uc1_robot_perception
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ProximityTask_
{
  using Type = ProximityTask_<ContainerAllocator>;

  explicit ProximityTask_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : min_point_robot(_init),
    min_point_vector(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->distance = 0.0f;
      this->link_id = "";
    }
  }

  explicit ProximityTask_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : min_point_robot(_alloc, _init),
    min_point_vector(_alloc, _init),
    link_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->distance = 0.0f;
      this->link_id = "";
    }
  }

  // field types and members
  using _min_point_robot_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _min_point_robot_type min_point_robot;
  using _min_point_vector_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _min_point_vector_type min_point_vector;
  using _distance_type =
    float;
  _distance_type distance;
  using _link_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _link_id_type link_id;

  // setters for named parameter idiom
  Type & set__min_point_robot(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->min_point_robot = _arg;
    return *this;
  }
  Type & set__min_point_vector(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->min_point_vector = _arg;
    return *this;
  }
  Type & set__distance(
    const float & _arg)
  {
    this->distance = _arg;
    return *this;
  }
  Type & set__link_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->link_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_perception::msg::ProximityTask_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_perception::msg::ProximityTask_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_perception::msg::ProximityTask_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_perception::msg::ProximityTask_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_perception__msg__ProximityTask
    std::shared_ptr<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_perception__msg__ProximityTask
    std::shared_ptr<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ProximityTask_ & other) const
  {
    if (this->min_point_robot != other.min_point_robot) {
      return false;
    }
    if (this->min_point_vector != other.min_point_vector) {
      return false;
    }
    if (this->distance != other.distance) {
      return false;
    }
    if (this->link_id != other.link_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const ProximityTask_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ProximityTask_

// alias to use template instance with default allocator
using ProximityTask =
  uc1_robot_perception::msg::ProximityTask_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace uc1_robot_perception

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK__STRUCT_HPP_
