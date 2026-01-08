#include "MissionManager.hpp"

MissionManager::MissionManager(std::shared_ptr<UR10eRobot> ur10e_robot,
                               std::shared_ptr<KukaRobot> kuka_robot,
                               std::shared_ptr<TfGoalBroadcaster> tf_broadcaster_node,
                               const RobotGoals& ur10e_goals,
                               const RobotGoals& kuka_goals)
  : ur10e_robot_(ur10e_robot),
    kuka_robot_(kuka_robot),
    tf_broadcaster_node_(tf_broadcaster_node),
    ur10e_goals_(ur10e_goals),
    kuka_goals_(kuka_goals),
    state_(MissionState::FSM_TEST_INIT)
{
    // empty constructor
}

void MissionManager::run()
{
  // Simple run loop. In a real application, you might spin in a dedicated thread or timer callback.
  while (rclcpp::ok() && state_ != MissionState::FSM_TEST_FINISHED)
  {
    update();
    // Sleep a bit to avoid busy-loop
    rclcpp::Rate(5).sleep();
    rclcpp::spin_some(rclcpp::Node::make_shared("spin_node"));
  }
}

// basic test fsm, one controller at time
void MissionManager::update()
{
  switch (state_)
  {
    case MissionState::FSM_TEST_INIT:
    {
      RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "State: INIT");

      // Transition to first step, put sanity checks here
      state_ = MissionState::FSM_TEST_MOVE_KUKA_JOINT;
      break;
    }

    case MissionState::FSM_TEST_MOVE_KUKA_JOINT:
    {
      RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Test KUKA joint goal");

      // setup control goals
      // auto joint_goal = kuka_goals_.joint_goals.at("kuka_test_q_goal");  // not needed now

      // TEST ONLY
      Eigen::VectorXd joint_goal(6);
      auto q_init = kuka_robot_->getJointPositions();
      joint_goal = q_init;
      joint_goal(0) = joint_goal(0) - 1.57;  // for joint limit testing
      joint_goal(1) = joint_goal(1) - 1.57;
      joint_goal(2) = joint_goal(2) + 1.57;

      // run loop
      Eigen::VectorXd q_err = Eigen::VectorXd::Zero(6);
      q_err = joint_goal;
      std::cout << q_init << "\n\n";
      exit(0);

      //// run joint pose loop (to be used in mission manager)
      kuka_robot_->runJointControlLoop(q_err, joint_goal);

      state_ = MissionState::FSM_TEST_MOVE_KUKA_CARTESIAN;
      break;
    }

    case MissionState::FSM_TEST_MOVE_KUKA_CARTESIAN:
    {
      RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Test KUKA cartesian goal");

      // Suppose we have a named pose goal "pose_A"
      auto kuka_poseA = kuka_goals_.pose_goals.at("pose_A");

      // Possibly broadcast TF or directly send the pose (TODO FIX THIS, NEED TO PASS TWO VECTORS)
      //tf_broadcaster_node_->broadcastTfGoal(kuka_poseA, "base_frame", "kuka_target");

      state_ = MissionState::FSM_TEST_MOVE_UR_JOINT;
      break;
    }

    case MissionState::FSM_TEST_MOVE_UR_JOINT:
    {
      RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Test UR Joint goal");

      // Suppose we have a named pose goal "pose_A"
      auto kuka_poseA = kuka_goals_.pose_goals.at("pose_A");

      state_ = MissionState::FSM_TEST_MOVE_UR_CARTESIAN;
      break;
    }

    case MissionState::FSM_TEST_MOVE_UR_CARTESIAN:
    {
      RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Test UR cartesian goal");

      // Suppose we have a named pose goal "pose_A"
      auto kuka_poseA = kuka_goals_.pose_goals.at("pose_A");

      state_ = MissionState::FSM_TEST_FINISHED;
      break;
    }

  }
}
