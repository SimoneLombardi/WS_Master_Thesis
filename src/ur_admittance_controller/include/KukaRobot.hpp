#ifndef KUKA_ROBOT_HPP
#define KUKA_ROBOT_HPP

#include "RobotInterface.hpp"

/**
 * @class KukaRobot
 * @brief Class defining the specific interface for a KUKA robot.
 */
class KukaRobot : public RobotInterface
{
public:
    void initialize(rclcpp::Node::SharedPtr node) override;
    void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg) override;
    void initJointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg);
    void updateTransforms() override; 
    void sendJointPositionCommand();
    void updateJointPositionCommand(Eigen::VectorXd q, Eigen::VectorXd qdot_des);
    Eigen::Affine3d getGenericTransformation(const std::string& target_frame, const std::string& source_frame);

    // ---------------------------------------- inverse kinematics (misc. and reaching task )
    bool initializeKDL();
    Eigen::MatrixXd computeJacobian(const std::string &frame_id);
    Eigen::MatrixXd attachRigidBodyJacobian(Eigen::MatrixXd link_jacobian, Eigen::Vector3d r_et);
    Eigen::MatrixXd computePseudoInverse(const Eigen::MatrixXd& jacobian);
    Eigen::VectorXd computeCartesianReachingTask(Eigen::Affine3d goal_frame, Eigen::Affine3d ctrl_frame);
    Eigen::Affine3d getTransformation(const std::string& target_frame, const std::string& source_frame);   // bypass tf update thread 

     // ---------------------------------------- getters
    std::vector<Eigen::Affine3d> getTransformations();
    Eigen::VectorXd getJointPositions();

    ~KukaRobot();

private:
    void tfUpdateLoop();  // update tf in background
    std::vector<std::string> frame_list_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_pub_;       // command interface
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_sub_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr mission_command_sub_;

    // startup configuration
    Eigen::VectorXd q_init_;
    bool initial_state_received_;

    // control command updater
    rclcpp::TimerBase::SharedPtr q_cmd_timer_;
    Eigen::VectorXd q_cmd_;
};

#endif // KUKA_ROBOT_HPP
