#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "geometry_msgs/msg/pose.hpp"



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