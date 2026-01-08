// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from uc1_robot_perception:msg/ProximityTaskArray.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__STRUCT_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'proximity_tasks'
#include "uc1_robot_perception/msg/detail/proximity_task__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_robot_perception__msg__ProximityTaskArray __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_perception__msg__ProximityTaskArray __declspec(deprecated)
#endif

namespace uc1_robot_perception
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ProximityTaskArray_
{
  using Type = ProximityTaskArray_<ContainerAllocator>;

  explicit ProximityTaskArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit ProximityTaskArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _proximity_tasks_type =
    std::vector<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator>>>;
  _proximity_tasks_type proximity_tasks;

  // setters for named parameter idiom
  Type & set__proximity_tasks(
    const std::vector<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uc1_robot_perception::msg::ProximityTask_<ContainerAllocator>>> & _arg)
  {
    this->proximity_tasks = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_perception__msg__ProximityTaskArray
    std::shared_ptr<uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_perception__msg__ProximityTaskArray
    std::shared_ptr<uc1_robot_perception::msg::ProximityTaskArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ProximityTaskArray_ & other) const
  {
    if (this->proximity_tasks != other.proximity_tasks) {
      return false;
    }
    return true;
  }
  bool operator!=(const ProximityTaskArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ProximityTaskArray_

// alias to use template instance with default allocator
using ProximityTaskArray =
  uc1_robot_perception::msg::ProximityTaskArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace uc1_robot_perception

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__PROXIMITY_TASK_ARRAY__STRUCT_HPP_
