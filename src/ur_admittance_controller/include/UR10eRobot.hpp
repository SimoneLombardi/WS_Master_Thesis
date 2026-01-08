#ifndef UR10E_ROBOT_HPP
#define UR10E_ROBOT_HPP

#include "RobotInterface.hpp"
#include <thread>
#include <mutex>

/**
 * @class UR10eRobot
 * @brief Class defining the specific interface for a UR10e robot.
 */
class UR10eRobot : public RobotInterface
{
public:
    void initialize(rclcpp::Node::SharedPtr node) override;
    void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg) override;
    void initJointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg);
    void updateTransforms() override; 
    void sendJointVelocityCommand(Eigen::VectorXd qdot_des);
    Eigen::Affine3d getGenericTransformation(const std::string& target_frame, const std::string& source_frame);

    // ---------------------------------------- inverse kinematics (misc. and reaching task )
    bool initializeKDL();
    Eigen::MatrixXd computeJacobian(const std::string &frame_id);
    Eigen::MatrixXd attachRigidBodyJacobian(Eigen::MatrixXd link_jacobian, Eigen::Vector3d r_et);
    Eigen::MatrixXd computePseudoInverse(const Eigen::MatrixXd& jacobian);
    Eigen::VectorXd computeCartesianReachingTask(Eigen::Affine3d goal_frame, Eigen::Affine3d ctrl_frame);

    // ---------------------------------------- inverse kinematics for sensor-based task

    // ft sensor handling
    void zeroFtSensor();
    void wristWrenchCallback(const geometry_msgs::msg::WrenchStamped::SharedPtr msg);
    void publishFilteredWrench(Eigen::VectorXd filt_wrench);


    // ---------------------------------------- getters
    std::vector<Eigen::Affine3d> getTransformations();
    Eigen::VectorXd getJointPositions();
    Eigen::VectorXd getWristWrench();

    ~UR10eRobot();        // custom destroyer to stop active threads

private:
    void tfUpdateLoop();  // update tf in background
    void broadcastTofFrames();

    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr urscript_publisher_;               // command interface 
    rclcpp::Publisher<geometry_msgs::msg::WrenchStamped>::SharedPtr filtered_wrench_publisher_;

    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr init_joint_state_sub_;   // hang until meaningful readings
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_sub_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr mission_command_sub_;
    rclcpp::Subscription<geometry_msgs::msg::WrenchStamped>::SharedPtr wrist_wrench_sub_;

    // startup configuration
    Eigen::VectorXd q_init_;
    bool initial_state_received_;

    // wrist wrench
    Eigen::VectorXd wrist_wrench_;

};

#endif // UR10E_ROBOT_HPP
