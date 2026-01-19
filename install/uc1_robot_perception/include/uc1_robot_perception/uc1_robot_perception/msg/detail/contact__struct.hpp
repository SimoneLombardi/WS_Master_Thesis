// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from uc1_robot_perception:msg/Contact.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__STRUCT_HPP_
#define UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'contact_location'
// Member 'contact_normal'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_robot_perception__msg__Contact __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_perception__msg__Contact __declspec(deprecated)
#endif

namespace uc1_robot_perception
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Contact_
{
  using Type = Contact_<ContainerAllocator>;

  explicit Contact_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : contact_location(_init),
    contact_normal(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->contact_intensity = 0.0f;
      this->reference_frame = "";
    }
  }

  explicit Contact_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : contact_location(_alloc, _init),
    contact_normal(_alloc, _init),
    reference_frame(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->contact_intensity = 0.0f;
      this->reference_frame = "";
    }
  }

  // field types and members
  using _contact_location_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _contact_location_type contact_location;
  using _contact_normal_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _contact_normal_type contact_normal;
  using _contact_intensity_type =
    float;
  _contact_intensity_type contact_intensity;
  using _reference_frame_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _reference_frame_type reference_frame;

  // setters for named parameter idiom
  Type & set__contact_location(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->contact_location = _arg;
    return *this;
  }
  Type & set__contact_normal(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->contact_normal = _arg;
    return *this;
  }
  Type & set__contact_intensity(
    const float & _arg)
  {
    this->contact_intensity = _arg;
    return *this;
  }
  Type & set__reference_frame(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->reference_frame = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_perception::msg::Contact_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_perception::msg::Contact_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_perception::msg::Contact_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_perception::msg::Contact_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_perception::msg::Contact_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_perception::msg::Contact_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_perception::msg::Contact_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_perception::msg::Contact_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_perception::msg::Contact_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_perception::msg::Contact_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_perception__msg__Contact
    std::shared_ptr<uc1_robot_perception::msg::Contact_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_perception__msg__Contact
    std::shared_ptr<uc1_robot_perception::msg::Contact_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Contact_ & other) const
  {
    if (this->contact_location != other.contact_location) {
      return false;
    }
    if (this->contact_normal != other.contact_normal) {
      return false;
    }
    if (this->contact_intensity != other.contact_intensity) {
      return false;
    }
    if (this->reference_frame != other.reference_frame) {
      return false;
    }
    return true;
  }
  bool operator!=(const Contact_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Contact_

// alias to use template instance with default allocator
using Contact =
  uc1_robot_perception::msg::Contact_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace uc1_robot_perception

#endif  // UC1_ROBOT_PERCEPTION__MSG__DETAIL__CONTACT__STRUCT_HPP_
