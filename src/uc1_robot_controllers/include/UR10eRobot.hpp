#ifndef UR10E_ROBOT_HPP
#define UR10E_ROBOT_HPP

#include "RobotInterface.hpp"
#include <thread>
#include <mutex>
// custom messages
#include "uc1_robot_perception/msg/proximity_task.hpp"
#include "uc1_robot_perception/msg/proximity_task_array.hpp"
#include "uc1_robot_perception/msg/contact.hpp"
#include "uc1_robot_perception/msg/contact_array.hpp"

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
    Eigen::MatrixXd computeAvoidanceJacobian(Eigen::Vector3d min_point, std::string frame_id);
    Eigen::VectorXd ComputePrioritizedControlLawDLS(std::vector<Eigen::MatrixXd> J_tasks, 
                                                    std::vector<Eigen::VectorXd> tasks, 
                                                    std::vector<float> alpha_tasks,
                                                    std::string link_id);
    Eigen::VectorXd computeProximityAvoidance(const uc1_robot_perception::msg::ProximityTask & task, float & activation);
    Eigen::VectorXd computeTactileAvoidance(const uc1_robot_perception::msg::Contact & task, float & activation);


    // ft sensor handling
    void zeroFtSensor();
    void wristWrenchCallback(const geometry_msgs::msg::WrenchStamped::SharedPtr msg);
    void publishFilteredWrench(Eigen::VectorXd filt_wrench);

    // dynamic gravity handling for floating configuration
    void setDynamicGravity();

    // ---------------------------------------- getters
    std::vector<Eigen::Affine3d> getTransformations();
    Eigen::VectorXd getJointPositions();
    Eigen::VectorXd getWristWrench();
    std::vector<std::string> getFrameList(); // SIMONE my methods
   
    // ---------------------------------------- controllers
    void runJointControlLoop(Eigen::VectorXd q_err, Eigen::VectorXd q_des);
    void runCartesianReachingLoop(std::string goal_frame, bool reached_goal);
    void runProximityControlLoop(std::string goal_frame, bool reached_goal);
    void runTactileControlLoop(std::string goal_frame, bool reached_goal);

    // -------------------------------------- sensor data callbacks
    void proximityTasksCallback(const uc1_robot_perception::msg::ProximityTaskArray::SharedPtr msg);
    void tactileTasksCallback(const uc1_robot_perception::msg::ContactArray::SharedPtr msg);

    // --------------------------------------- sensory data utils
    void swapProximityBuffers();
    uc1_robot_perception::msg::ProximityTask getMinDistTask(const uc1_robot_perception::msg::ProximityTaskArray & tasks_msg);
    void displayProximityTask(const uc1_robot_perception::msg::ProximityTask & task);

    void swapTactileBuffers();
    uc1_robot_perception::msg::Contact getMaxForceTask(const uc1_robot_perception::msg::ContactArray & tasks_msg);
    void displayTactileTask(const uc1_robot_perception::msg::Contact & task);

    double DecreasingBellShapedFunction(double xmin, double xmax, double ymin, double ymax, double x);
    double IncreasingBellShapedFunction(double xmin, double xmax, double ymin, double ymax, double x);

    // admittance task for KUKA 
    Eigen::Vector3d projectTaskOnRobotBase(
                const geometry_msgs::msg::Vector3& sensor_position,
                const geometry_msgs::msg::Vector3& sensor_z_normal,
                float measured_force,
                const std::string& link_frame,
                const std::string& base_frame);

    // visualization
    void publishArrowMarker(
                const Eigen::Vector3d& origin,
                const Eigen::Vector3d& vector,
                const std::string& frame_id,
                const std::string& ns,
                int id,
                rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher);

    ~UR10eRobot();             // custom destroyer to stop active threads

private:
    void tfUpdateLoop();       // update tf in background
    void broadcastTofFrames();

    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> tf_static_broadcaster_;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr urscript_publisher_;               // command interface 
    rclcpp::Publisher<geometry_msgs::msg::WrenchStamped>::SharedPtr filtered_wrench_publisher_;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr control_task_viz_publisher_;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr control_task_base_viz_publisher_;

    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr init_joint_state_sub_;   // hang until meaningful readings
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_sub_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr mission_command_sub_;
    rclcpp::Subscription<geometry_msgs::msg::WrenchStamped>::SharedPtr wrist_wrench_sub_;
    rclcpp::Subscription<uc1_robot_perception::msg::ProximityTaskArray>::SharedPtr proximity_tasks_sub_;  // proximity task
    rclcpp::Subscription<uc1_robot_perception::msg::ContactArray>::SharedPtr tactile_tasks_sub_;  // tactile task

    // proximity buffered update 
    uc1_robot_perception::msg::ProximityTaskArray proxy_front_tasks_;
    uc1_robot_perception::msg::ProximityTaskArray proxy_back_tasks_;
    std::mutex proxy_buffer_mutex_;
    bool proxy_new_data_available_ = false;

    // tactile buffered update
    uc1_robot_perception::msg::ContactArray tactile_front_tasks_;
    uc1_robot_perception::msg::ContactArray tactile_back_tasks_;
    std::mutex tactile_buffer_mutex_;
    bool tactile_new_data_available_ = false;

    // startup configuration
    Eigen::VectorXd q_init_;
    bool initial_state_received_;

    // wrist wrench
    Eigen::VectorXd wrist_wrench_;

};

#endif // UR10E_ROBOT_HPP
