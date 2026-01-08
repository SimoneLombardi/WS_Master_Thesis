// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from uc1_robot_controllers_interfaces:msg/MoveRobotGoal.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__STRUCT_HPP_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'translation'
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_point__struct.hpp"
// Member 'orientation'
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_orient__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_robot_controllers_interfaces__msg__MoveRobotGoal __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_controllers_interfaces__msg__MoveRobotGoal __declspec(deprecated)
#endif

namespace uc1_robot_controllers_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MoveRobotGoal_
{
  using Type = MoveRobotGoal_<ContainerAllocator>;

  explicit MoveRobotGoal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : translation(_init),
    orientation(_init)
  {
    (void)_init;
  }

  explicit MoveRobotGoal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : translation(_alloc, _init),
    orientation(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _translation_type =
    uc1_robot_controllers_interfaces::msg::MoveRobotPoint_<ContainerAllocator>;
  _translation_type translation;
  using _orientation_type =
    uc1_robot_controllers_interfaces::msg::MoveRobotOrient_<ContainerAllocator>;
  _orientation_type orientation;

  // setters for named parameter idiom
  Type & set__translation(
    const uc1_robot_controllers_interfaces::msg::MoveRobotPoint_<ContainerAllocator> & _arg)
  {
    this->translation = _arg;
    return *this;
  }
  Type & set__orientation(
    const uc1_robot_controllers_interfaces::msg::MoveRobotOrient_<ContainerAllocator> & _arg)
  {
    this->orientation = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_controllers_interfaces__msg__MoveRobotGoal
    std::shared_ptr<uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_controllers_interfaces__msg__MoveRobotGoal
    std::shared_ptr<uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobotGoal_ & other) const
  {
    if (this->translation != other.translation) {
      return false;
    }
    if (this->orientation != other.orientation) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobotGoal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobotGoal_

// alias to use template instance with default allocator
using MoveRobotGoal =
  uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace uc1_robot_controllers_interfaces

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__MSG__DETAIL__MOVE_ROBOT_GOAL__STRUCT_HPP_
