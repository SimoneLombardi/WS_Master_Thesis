// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from uc1_robot_controllers_interfaces:action/MoveRobotTP.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT_TP__STRUCT_HPP_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT_TP__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'goal'
#include "uc1_robot_controllers_interfaces/msg/detail/move_robot_goal__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal __declspec(deprecated)
#endif

namespace uc1_robot_controllers_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveRobotTP_Goal_
{
  using Type = MoveRobotTP_Goal_<ContainerAllocator>;

  explicit MoveRobotTP_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->init_config_name = "";
    }
  }

  explicit MoveRobotTP_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal(_alloc, _init),
    init_config_name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->init_config_name = "";
    }
  }

  // field types and members
  using _goal_type =
    uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator>;
  _goal_type goal;
  using _init_config_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _init_config_name_type init_config_name;

  // setters for named parameter idiom
  Type & set__goal(
    const uc1_robot_controllers_interfaces::msg::MoveRobotGoal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }
  Type & set__init_config_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->init_config_name = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Goal
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobotTP_Goal_ & other) const
  {
    if (this->goal != other.goal) {
      return false;
    }
    if (this->init_config_name != other.init_config_name) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobotTP_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobotTP_Goal_

// alias to use template instance with default allocator
using MoveRobotTP_Goal =
  uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces


#ifndef _WIN32
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Result __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Result __declspec(deprecated)
#endif

namespace uc1_robot_controllers_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveRobotTP_Result_
{
  using Type = MoveRobotTP_Result_<ContainerAllocator>;

  explicit MoveRobotTP_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = "";
    }
  }

  explicit MoveRobotTP_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->result = "";
    }
  }

  // field types and members
  using _result_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__result(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Result
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Result
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobotTP_Result_ & other) const
  {
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobotTP_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobotTP_Result_

// alias to use template instance with default allocator
using MoveRobotTP_Result =
  uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces


#ifndef _WIN32
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback __declspec(deprecated)
#endif

namespace uc1_robot_controllers_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveRobotTP_Feedback_
{
  using Type = MoveRobotTP_Feedback_<ContainerAllocator>;

  explicit MoveRobotTP_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->linvel_norm = 0.0;
      this->angvel_norm = 0.0;
    }
  }

  explicit MoveRobotTP_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->linvel_norm = 0.0;
      this->angvel_norm = 0.0;
    }
  }

  // field types and members
  using _linvel_norm_type =
    double;
  _linvel_norm_type linvel_norm;
  using _angvel_norm_type =
    double;
  _angvel_norm_type angvel_norm;

  // setters for named parameter idiom
  Type & set__linvel_norm(
    const double & _arg)
  {
    this->linvel_norm = _arg;
    return *this;
  }
  Type & set__angvel_norm(
    const double & _arg)
  {
    this->angvel_norm = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_Feedback
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobotTP_Feedback_ & other) const
  {
    if (this->linvel_norm != other.linvel_norm) {
      return false;
    }
    if (this->angvel_norm != other.angvel_norm) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobotTP_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobotTP_Feedback_

// alias to use template instance with default allocator
using MoveRobotTP_Feedback =
  uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "uc1_robot_controllers_interfaces/action/detail/move_robot_tp__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Request __declspec(deprecated)
#endif

namespace uc1_robot_controllers_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveRobotTP_SendGoal_Request_
{
  using Type = MoveRobotTP_SendGoal_Request_<ContainerAllocator>;

  explicit MoveRobotTP_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit MoveRobotTP_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Request
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Request
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobotTP_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobotTP_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobotTP_SendGoal_Request_

// alias to use template instance with default allocator
using MoveRobotTP_SendGoal_Request =
  uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Response __declspec(deprecated)
#endif

namespace uc1_robot_controllers_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveRobotTP_SendGoal_Response_
{
  using Type = MoveRobotTP_SendGoal_Response_<ContainerAllocator>;

  explicit MoveRobotTP_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit MoveRobotTP_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Response
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_SendGoal_Response
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobotTP_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobotTP_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobotTP_SendGoal_Response_

// alias to use template instance with default allocator
using MoveRobotTP_SendGoal_Response =
  uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

namespace uc1_robot_controllers_interfaces
{

namespace action
{

struct MoveRobotTP_SendGoal
{
  using Request = uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Request;
  using Response = uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal_Response;
};

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Request __declspec(deprecated)
#endif

namespace uc1_robot_controllers_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveRobotTP_GetResult_Request_
{
  using Type = MoveRobotTP_GetResult_Request_<ContainerAllocator>;

  explicit MoveRobotTP_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit MoveRobotTP_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Request
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Request
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobotTP_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobotTP_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobotTP_GetResult_Request_

// alias to use template instance with default allocator
using MoveRobotTP_GetResult_Request =
  uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces


// Include directives for member types
// Member 'result'
// already included above
// #include "uc1_robot_controllers_interfaces/action/detail/move_robot_tp__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Response __declspec(deprecated)
#endif

namespace uc1_robot_controllers_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveRobotTP_GetResult_Response_
{
  using Type = MoveRobotTP_GetResult_Response_<ContainerAllocator>;

  explicit MoveRobotTP_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit MoveRobotTP_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Response
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_GetResult_Response
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobotTP_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobotTP_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobotTP_GetResult_Response_

// alias to use template instance with default allocator
using MoveRobotTP_GetResult_Response =
  uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

namespace uc1_robot_controllers_interfaces
{

namespace action
{

struct MoveRobotTP_GetResult
{
  using Request = uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Request;
  using Response = uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult_Response;
};

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "uc1_robot_controllers_interfaces/action/detail/move_robot_tp__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_FeedbackMessage __declspec(deprecated)
#endif

namespace uc1_robot_controllers_interfaces
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct MoveRobotTP_FeedbackMessage_
{
  using Type = MoveRobotTP_FeedbackMessage_<ContainerAllocator>;

  explicit MoveRobotTP_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit MoveRobotTP_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_FeedbackMessage
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__uc1_robot_controllers_interfaces__action__MoveRobotTP_FeedbackMessage
    std::shared_ptr<uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveRobotTP_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveRobotTP_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveRobotTP_FeedbackMessage_

// alias to use template instance with default allocator
using MoveRobotTP_FeedbackMessage =
  uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace uc1_robot_controllers_interfaces
{

namespace action
{

struct MoveRobotTP
{
  /// The goal message defined in the action definition.
  using Goal = uc1_robot_controllers_interfaces::action::MoveRobotTP_Goal;
  /// The result message defined in the action definition.
  using Result = uc1_robot_controllers_interfaces::action::MoveRobotTP_Result;
  /// The feedback message defined in the action definition.
  using Feedback = uc1_robot_controllers_interfaces::action::MoveRobotTP_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = uc1_robot_controllers_interfaces::action::MoveRobotTP_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = uc1_robot_controllers_interfaces::action::MoveRobotTP_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = uc1_robot_controllers_interfaces::action::MoveRobotTP_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct MoveRobotTP MoveRobotTP;

}  // namespace action

}  // namespace uc1_robot_controllers_interfaces

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT_TP__STRUCT_HPP_
