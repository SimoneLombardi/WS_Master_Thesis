#pragma once

#include <rclcpp/rclcpp.hpp>
#include <map>
#include <string>
#include <vector>
#include <memory>

#include "geometry_msgs/msg/pose.hpp"

#include "rclcpp/rclcpp.hpp"
#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"
#include "TfGoalBroadcaster.hpp"

// named goals for joints and ee represented as hash tables (use the same name for the mission and the goal)
struct RobotGoals
{
  std::map<std::string, std::vector<double>> joint_goals;
  std::map<std::string, geometry_msgs::msg::Pose> pose_goals;
};

// mission states (phase 1 here is from 1 to 45 in CRF table)
/*
enum class MissionState
{
  PHASE_1_INIT,
  PHASE_1_CARTESIAN_MOVE_KUKA_FLANGE_ORIENTATION_UPWARDS,
  PHASE_1_JOINT_MOVE_UR10E_TUCKED,
  PHASE_1_CARTESIAN_MOVE_KUKA_FLANGE_ORIENTATION_CARDOOR,
  PHASE_1_CARTESIAN_MOVE_KUKA_FLANGE_POSITION_CARDOOR,
  PHASE_1_JOINT_MOVE_UR10E_PLANAR_CONFIG,
  PHASE_1_CARTESIAN_MOVE_UR10E_FLANGE_WINDSHIELD,
  PHASE_1_WAIT_FOR_GRIPPER,
  PHASE_1_CARTESIAN_MOVE_UR10E_INSERTION
};
*/

enum class MissionState
{
    FSM_TEST_INIT,
    FSM_TEST_MOVE_KUKA_JOINT,
    FSM_TEST_MOVE_KUKA_CARTESIAN,
    FSM_TEST_MOVE_UR_JOINT,
    FSM_TEST_MOVE_UR_CARTESIAN,
    FSM_TEST_FINISHED
};

class MissionManager
{
public:
  MissionManager(std::shared_ptr<UR10eRobot> ur10e_robot,
                 std::shared_ptr<KukaRobot> kuka_robot,
                 std::shared_ptr<TfGoalBroadcaster> tf_broadcaster_node,
                 const RobotGoals& ur10e_goals,
                 const RobotGoals& kuka_goals);

  ~MissionManager() = default;

  void run();

private:
  /**
   * @brief Update method that advances the state machine steps
   */
  void update();

  // Shared pointers to the robot interfaces
  std::shared_ptr<UR10eRobot> ur10e_robot_;
  std::shared_ptr<KukaRobot>  kuka_robot_;
  std::shared_ptr<TfGoalBroadcaster> tf_broadcaster_node_;

  // References to the robot goals (pre-defined)
  const RobotGoals& ur10e_goals_;
  const RobotGoals& kuka_goals_;

  // Current mission state
  MissionState state_;
};

