// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from uc1_robot_controllers_interfaces:action/MoveRobot.idl
// generated code does not contain a copyright notice

#ifndef UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT__BUILDER_HPP_
#define UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "uc1_robot_controllers_interfaces/action/detail/move_robot__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace uc1_robot_controllers_interfaces
{

namespace action
{

namespace builder
{

class Init_MoveRobot_Goal_jacobian_type_code
{
public:
  explicit Init_MoveRobot_Goal_jacobian_type_code(::uc1_robot_controllers_interfaces::action::MoveRobot_Goal & msg)
  : msg_(msg)
  {}
  ::uc1_robot_controllers_interfaces::action::MoveRobot_Goal jacobian_type_code(::uc1_robot_controllers_interfaces::action::MoveRobot_Goal::_jacobian_type_code_type arg)
  {
    msg_.jacobian_type_code = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_Goal msg_;
};

class Init_MoveRobot_Goal_init_config_code
{
public:
  explicit Init_MoveRobot_Goal_init_config_code(::uc1_robot_controllers_interfaces::action::MoveRobot_Goal & msg)
  : msg_(msg)
  {}
  Init_MoveRobot_Goal_jacobian_type_code init_config_code(::uc1_robot_controllers_interfaces::action::MoveRobot_Goal::_init_config_code_type arg)
  {
    msg_.init_config_code = std::move(arg);
    return Init_MoveRobot_Goal_jacobian_type_code(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_Goal msg_;
};

class Init_MoveRobot_Goal_goal
{
public:
  Init_MoveRobot_Goal_goal()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveRobot_Goal_init_config_code goal(::uc1_robot_controllers_interfaces::action::MoveRobot_Goal::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return Init_MoveRobot_Goal_init_config_code(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::action::MoveRobot_Goal>()
{
  return uc1_robot_controllers_interfaces::action::builder::Init_MoveRobot_Goal_goal();
}

}  // namespace uc1_robot_controllers_interfaces


namespace uc1_robot_controllers_interfaces
{

namespace action
{

namespace builder
{

class Init_MoveRobot_Result_result
{
public:
  Init_MoveRobot_Result_result()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::uc1_robot_controllers_interfaces::action::MoveRobot_Result result(::uc1_robot_controllers_interfaces::action::MoveRobot_Result::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::action::MoveRobot_Result>()
{
  return uc1_robot_controllers_interfaces::action::builder::Init_MoveRobot_Result_result();
}

}  // namespace uc1_robot_controllers_interfaces


namespace uc1_robot_controllers_interfaces
{

namespace action
{

namespace builder
{

class Init_MoveRobot_Feedback_angvel_norm
{
public:
  explicit Init_MoveRobot_Feedback_angvel_norm(::uc1_robot_controllers_interfaces::action::MoveRobot_Feedback & msg)
  : msg_(msg)
  {}
  ::uc1_robot_controllers_interfaces::action::MoveRobot_Feedback angvel_norm(::uc1_robot_controllers_interfaces::action::MoveRobot_Feedback::_angvel_norm_type arg)
  {
    msg_.angvel_norm = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_Feedback msg_;
};

class Init_MoveRobot_Feedback_linvel_norm
{
public:
  Init_MoveRobot_Feedback_linvel_norm()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveRobot_Feedback_angvel_norm linvel_norm(::uc1_robot_controllers_interfaces::action::MoveRobot_Feedback::_linvel_norm_type arg)
  {
    msg_.linvel_norm = std::move(arg);
    return Init_MoveRobot_Feedback_angvel_norm(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::action::MoveRobot_Feedback>()
{
  return uc1_robot_controllers_interfaces::action::builder::Init_MoveRobot_Feedback_linvel_norm();
}

}  // namespace uc1_robot_controllers_interfaces


namespace uc1_robot_controllers_interfaces
{

namespace action
{

namespace builder
{

class Init_MoveRobot_SendGoal_Request_goal
{
public:
  explicit Init_MoveRobot_SendGoal_Request_goal(::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Request goal(::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Request msg_;
};

class Init_MoveRobot_SendGoal_Request_goal_id
{
public:
  Init_MoveRobot_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveRobot_SendGoal_Request_goal goal_id(::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveRobot_SendGoal_Request_goal(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Request>()
{
  return uc1_robot_controllers_interfaces::action::builder::Init_MoveRobot_SendGoal_Request_goal_id();
}

}  // namespace uc1_robot_controllers_interfaces


namespace uc1_robot_controllers_interfaces
{

namespace action
{

namespace builder
{

class Init_MoveRobot_SendGoal_Response_stamp
{
public:
  explicit Init_MoveRobot_SendGoal_Response_stamp(::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Response stamp(::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Response msg_;
};

class Init_MoveRobot_SendGoal_Response_accepted
{
public:
  Init_MoveRobot_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveRobot_SendGoal_Response_stamp accepted(::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_MoveRobot_SendGoal_Response_stamp(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::action::MoveRobot_SendGoal_Response>()
{
  return uc1_robot_controllers_interfaces::action::builder::Init_MoveRobot_SendGoal_Response_accepted();
}

}  // namespace uc1_robot_controllers_interfaces


namespace uc1_robot_controllers_interfaces
{

namespace action
{

namespace builder
{

class Init_MoveRobot_GetResult_Request_goal_id
{
public:
  Init_MoveRobot_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Request goal_id(::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Request>()
{
  return uc1_robot_controllers_interfaces::action::builder::Init_MoveRobot_GetResult_Request_goal_id();
}

}  // namespace uc1_robot_controllers_interfaces


namespace uc1_robot_controllers_interfaces
{

namespace action
{

namespace builder
{

class Init_MoveRobot_GetResult_Response_result
{
public:
  explicit Init_MoveRobot_GetResult_Response_result(::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Response result(::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Response msg_;
};

class Init_MoveRobot_GetResult_Response_status
{
public:
  Init_MoveRobot_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveRobot_GetResult_Response_result status(::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_MoveRobot_GetResult_Response_result(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::action::MoveRobot_GetResult_Response>()
{
  return uc1_robot_controllers_interfaces::action::builder::Init_MoveRobot_GetResult_Response_status();
}

}  // namespace uc1_robot_controllers_interfaces


namespace uc1_robot_controllers_interfaces
{

namespace action
{

namespace builder
{

class Init_MoveRobot_FeedbackMessage_feedback
{
public:
  explicit Init_MoveRobot_FeedbackMessage_feedback(::uc1_robot_controllers_interfaces::action::MoveRobot_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::uc1_robot_controllers_interfaces::action::MoveRobot_FeedbackMessage feedback(::uc1_robot_controllers_interfaces::action::MoveRobot_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_FeedbackMessage msg_;
};

class Init_MoveRobot_FeedbackMessage_goal_id
{
public:
  Init_MoveRobot_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveRobot_FeedbackMessage_feedback goal_id(::uc1_robot_controllers_interfaces::action::MoveRobot_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveRobot_FeedbackMessage_feedback(msg_);
  }

private:
  ::uc1_robot_controllers_interfaces::action::MoveRobot_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::uc1_robot_controllers_interfaces::action::MoveRobot_FeedbackMessage>()
{
  return uc1_robot_controllers_interfaces::action::builder::Init_MoveRobot_FeedbackMessage_goal_id();
}

}  // namespace uc1_robot_controllers_interfaces

#endif  // UC1_ROBOT_CONTROLLERS_INTERFACES__ACTION__DETAIL__MOVE_ROBOT__BUILDER_HPP_
