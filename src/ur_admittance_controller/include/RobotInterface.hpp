#ifndef ROBOT_INTERFACE_HPP
#define ROBOT_INTERFACE_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2_ros/transform_broadcaster.h"
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/wrench_stamped.hpp>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <string>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/chainjnttojacsolver.hpp>
#include <kdl_parser/kdl_parser.hpp>
#include <urdf/model.h>

/**
 * @class RobotInterface
 * @brief Abstract base class defining the common interface for arbitrary robot models.
 */
class RobotInterface
{
public:
    virtual ~RobotInterface() = default;

    /**
     * @brief Initialize the robot-specific subscribers and publishers.
     * @param node Shared pointer to the ROS2 node.
     */
    virtual void initialize(rclcpp::Node::SharedPtr node) = 0;

    /**
     * @brief Handle the joint state callback for the robot.
     * @param msg Shared pointer to the received JointState message.
     */
    virtual void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg) = 0;

    /**
     * @brief Handle the mission command callback.
     * @param msg Shared pointer to the received mission command (String message).
     */
    //virtual void missionCommandCallback(const std_msgs::msg::String::SharedPtr msg) = 0;

    /**
     * @brief Update the stored transformations for the robot's frames.
     */
    virtual void updateTransforms() = 0;


protected:
    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
    // TODO change these to fixed size arrays
    std::vector<std::string> frame_list_;                  // List of frames to listen for
    std::vector<Eigen::Affine3d> transformations_;         // Array of Eigen transformations

    rclcpp::Node::SharedPtr node_;                         // ROS2 node for handling communication

    // tf updater thread (double buffering)
    std::thread tf_update_thread_;    
    std::mutex transformations_mutex_; 
    bool stop_tf_thread_ = false; 
    std::vector<Eigen::Affine3d> tf_read_buffer_, tf_write_buffer_;
    std::mutex tf_buffer_mutex_;

    // joint state
    Eigen::VectorXd q_;
    Eigen::VectorXd qdot_;
    Eigen::VectorXd qdot_cmd_;
    Eigen::VectorXd q_efforts_;
    Eigen::VectorXd q_target_;
    std::vector<std::string> joint_names_;
    std::vector<std::string> ordered_joint_names_;

    // inverse kinematics
    KDL::Tree kdl_tree_;
    KDL::Chain kdl_chain_;
    std::unordered_map<std::string, KDL::Chain> kdl_chains_;
    std::unordered_map<std::string, std::shared_ptr<KDL::ChainFkSolverPos_recursive>> fk_solvers_;
    std::unordered_map<std::string, std::shared_ptr<KDL::ChainJntToJacSolver>> jacobian_solvers_;
    std::unordered_map<std::string, KDL::Jacobian> jacobians_;
};

#endif // ROBOT_INTERFACE_HPP
