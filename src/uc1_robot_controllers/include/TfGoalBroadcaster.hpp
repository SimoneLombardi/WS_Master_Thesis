#pragma once

#include <string>
#include <Eigen/Dense>
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/static_transform_broadcaster.h"

class TfGoalBroadcaster
{
public:

  TfGoalBroadcaster(const rclcpp::Node::SharedPtr& node)
  : node_(node)
  {
    static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(node_);
  }

  /**
   * @brief Broadcast a static transform using a given position, RPY orientation, and frame names.
   *
   * @param position     Eigen::Vector3d with x, y, z coordinates
   * @param rpy          Eigen::Vector3d with roll, pitch, yaw angles (in radians)
   * @param parent_frame Name of the parent frame (e.g. "world" or "map")
   * @param child_frame  Name of the child frame to broadcast
   */
  void broadcastStaticTransform(
    const Eigen::Vector3d& position,
    const Eigen::Vector3d& rpy,
    const std::string& parent_frame,
    const std::string& child_frame);

private:
  rclcpp::Node::SharedPtr node_;
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> static_broadcaster_;
};
