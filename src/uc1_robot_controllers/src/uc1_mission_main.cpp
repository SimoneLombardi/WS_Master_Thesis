#include <rclcpp/rclcpp.hpp>
#include "MissionHelpers.hpp"
#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"
#include "TfGoalBroadcaster.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  // Create a node
  auto node = rclcpp::Node::make_shared("mission_manager_node");

  // Instantiate robot interfaces
  auto ur10e_robot = std::make_shared<UR10eRobot>();
  auto kuka_robot = std::make_shared<KukaRobot>();
  auto tf_broadcaster_node = std::make_shared<TfGoalBroadcaster>(node);

  kuka_robot->initialize(node);
  ur10e_robot->initialize(node);

  // spin callbacks
  auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
  executor->add_node(node);
  std::thread spin_thread([executor]()
                          { executor->spin(); });

  // sample goals, define specific ones in configuration files
  RobotGoals ur10e_goals;
  ur10e_goals.joint_goals["ur_test_q_goal"] = {0.0, -1.57, 0.0, -1.57, 0.0, 0.0};
  ur10e_goals.pose_goals["ur_test_cart_goal"] = []()
  {
    geometry_msgs::msg::Pose p;
    p.position.x = 0.5;
    p.position.y = 0.0;
    p.position.z = 0.3;
    p.orientation.w = 1.0;
    p.orientation.x = 0.0;
    p.orientation.y = 0.0;
    p.orientation.z = 0.0;
    return p;
  }();

  RobotGoals kuka_goals;
  kuka_goals.joint_goals["kuka_test_q_goal"] = {0.0, 1.0, 0.0, 1.0, 0.0, -1.0};
  kuka_goals.pose_goals["kuka_test_cart_goal"] = []()
  {
    geometry_msgs::msg::Pose p;
    p.position.x = 0.5;
    p.position.y = 0.0;
    p.position.z = 0.3;
    p.orientation.w = 1.0;
    p.orientation.x = 0.0;
    p.orientation.y = 0.0;
    p.orientation.z = 0.0;
    return p;
  }();


  // initial fsm state
  MissionState state = MissionState::FSM_TEST_INIT;

  while (rclcpp::ok() && state != MissionState::FSM_TEST_FINISHED)
  {
    switch (state)
    {
      case MissionState::FSM_TEST_INIT:
      {
        RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "State: INIT");

        // Transition to first step, put sanity checks here
        state = MissionState::FSM_TEST_MOVE_KUKA_JOINT;
        break;
      }

      case MissionState::FSM_TEST_MOVE_KUKA_JOINT:
      {
        RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Test KUKA joint goal");

        // setup control goals
        // auto joint_goal = kuka_goals_.joint_goals.at("kuka_test_q_goal");  // not needed now

        // TEST ONLY
        Eigen::VectorXd joint_goal(6);
        auto q_init = kuka_robot->getJointPositions();
        joint_goal = q_init;
        //joint_goal(0) = joint_goal(0) - 1.57; // for joint limit testing
        joint_goal(1) = joint_goal(1) - 1.57;
        joint_goal(2) = joint_goal(2) + 1.57;
        std::cout << q_init << "\n\n";

        // run loop
        Eigen::VectorXd q_err = Eigen::VectorXd::Zero(6);
        q_err = joint_goal;
        std::cout << q_err.norm() << "\n\n";

        //// run joint pose loop (to be used in mission manager)
        kuka_robot->runJointControlLoop(q_err, joint_goal);

        state = MissionState::FSM_TEST_MOVE_KUKA_CARTESIAN;
        break;
      }

      case MissionState::FSM_TEST_MOVE_KUKA_CARTESIAN:
      {
        RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Test KUKA cartesian goal");

        // TODO check cartesian goal, need to split again in position and rpy
        // auto joint_goal = kuka_goals_.joint_goals.at("kuka_test_q_goal");  // not needed now

        // TEST ONLY
        Eigen::Vector3d position(1.2, 0.0, 1.0);
        Eigen::Vector3d rpy(0.0, 0.0, 0.0);
        std::string parent_frame = "kuka_base_link";
        std::string goal_frame  = "ik_tool_frame_kuka";
        tf_broadcaster_node->broadcastStaticTransform(position, rpy, parent_frame, goal_frame);

        RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Starting main loop...");
        std::this_thread::sleep_for(2000ms); // 2 sec break before starting
        bool reached_goal = false;
        kuka_robot->runCartesianReachingLoop(goal_frame, reached_goal);

        state = MissionState::FSM_TEST_MOVE_UR_JOINT;
        break;
      }

      case MissionState::FSM_TEST_MOVE_UR_JOINT:
      {
        RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Test UR joint goal");

        // setup control goals
        // auto joint_goal = kuka_goals_.joint_goals.at("kuka_test_q_goal");  // not needed now

        // TEST ONLY
        Eigen::VectorXd q_des(6);
        q_des << -3.14159, -2.10757, -1.83066, -0.774163, -1.5708, -0.0300288;
        Eigen::VectorXd q_err = Eigen::VectorXd::Zero(6);
        q_err = q_des;
        std::cout << q_err.norm() << "\n\n";
        // run joint pose loop (to be used in mission manager)
        ur10e_robot->runJointControlLoop(q_err, q_des);

        state = MissionState::FSM_TEST_MOVE_UR_CARTESIAN;
        break;
      }

      case MissionState::FSM_TEST_MOVE_UR_CARTESIAN:
      {
        RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Test UR cartesian goal");

        // TODO check cartesian goal, need to split again in position and rpy
        // auto joint_goal = kuka_goals_.joint_goals.at("kuka_test_q_goal");  // not needed now

        // TEST ONLY
        Eigen::Vector3d position(0.7, 0.0, 0.5);
        Eigen::Vector3d rpy(0.0, 0.0, 0.0);
        std::string parent_frame = "base_link";
        std::string goal_frame  = "ik_reach_goal";
        tf_broadcaster_node->broadcastStaticTransform(position, rpy, parent_frame, goal_frame);

        RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Starting main loop...");
        std::this_thread::sleep_for(2000ms); // 2 sec break before starting
        bool reached_goal = false;
        ur10e_robot->runCartesianReachingLoop(goal_frame, reached_goal);

        state = MissionState::FSM_TEST_FINISHED;
        break;
      }

    }
  }

  executor->cancel();
  if (spin_thread.joinable())
  {
      spin_thread.join();
  }

  rclcpp::shutdown();
  RCLCPP_INFO(rclcpp::get_logger("mission_manager"), "Kuka node shut down successfully.");

  rclcpp::shutdown();
  return 0;
}
