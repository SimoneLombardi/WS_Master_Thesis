#ifndef JOINT_ROBOT_HPP
#define JOINT_ROBOT_HPP

#include <cmath>
#include <map>

#include "RobotInterface.hpp" // keep this for the RobotInterface include block
#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"

// action server includes
#include "TfGoalBroadcaster.hpp"
#include "uc1_robot_controllers_interfaces/action/move_robot.hpp"
#include "uc1_robot_perception/msg/proximity_task_array.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_action/create_server.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "std_msgs/msg/string.hpp"

#include "TPComputation.hpp"

//#define JOINT_ROBOT_LINKS 12 // Total number of joints for both robots (6 for Kuka and 6 for UR10e)

#define KUKA_ROBOT 0
#define UR10_ROBOT 1

enum class RobotInitializationState
{
    // <KUKA_INIT_CONFIG>_<UR10_INIT_CONFIG>
    SINGULARITY_SINGULARITY,    
    SINGULARITY_MOBILITY,
    MOBILITY_SINGULARITY,
    MOBILITY_MOBILITY,
};

class JointRobot
{  
    public:
        // ---------------------------------------- PUBLIC METHODS ---------------------------------------------------------- //
        // INIT METHOD inizializza le istanze dei due robot e i vari parametri ed dati
        void initialize(rclcpp::Node::SharedPtr node_joint_robot, rclcpp::Node::SharedPtr node_1, rclcpp::Node::SharedPtr node_2); // initialize 2 different robot nodes

        // setter methods 
        // inizializzano e/o aggiornano i parametri del JointRobot
        void     setJoint_nameVector();
        void     setJoint_qVector();
        void     setJoint_jacobian();
        void     setJoint_jacobian_complete();
        void     setJoint_jacobian_slidingUR10();
        void     setJoint_transformChain();
        void     setJoint_initConfig();

        // updater methods
        void     update_robotInitConfigState(const RobotInitializationState& init_state);

        // getter methods
        // restituiscono i parametri del JointRobot
        std::vector<std::string>     getJoint_nameVector(int select); // Get joint names vector, select 0 for all names, 1 for ordered names
        Eigen::VectorXd              getJoint_qVector();
        std::vector<Eigen::VectorXd> getJoint_initStateVector(); 
        Eigen::MatrixXd              getJoint_jacobian();
        Eigen::MatrixXd              getJoint_jacobian_complete();
        Eigen::MatrixXd              getJoint_jacobian_slidingUR10(); // Get joint jacobian with sliding UR10e
        std::vector<Eigen::Affine3d> getJoint_transformChain();

        Eigen::Affine3d              getGenericTransformation(const std::string& target_frame, const std::string& source_frame); // Get transformation between frames
        RobotInitializationState     getRobotInitializationState() const;

        // controller methods
        void reachJointPosition_single(int robot_code, Eigen::VectorXd q_err, Eigen::VectorXd q_des); // Run joint control loop
        void reachJointPosition(Eigen::VectorXd q_err, Eigen::VectorXd q_des); // Run joint control loop for both robots
        void runCartesianReachingLoop(std::string goal_frame, bool reached_goal); // Run Cartesian reaching loop for both robots

        void sendBaseVelocityCommand(Eigen::VectorXd vel); // Send base velocity command to Kuka robot

        // sub callbacks
        void proximityTaskCallback(const uc1_robot_perception::msg::ProximityTaskArray::SharedPtr msg); 

        // varie
        Eigen::MatrixXd computePseudoInverse(const Eigen::MatrixXd& jacobian, const std::vector<float> partition); // Compute pseudo-inverse of a matrix
        Eigen::VectorXd trasformVector(const std::string& source_frame, const std::string& target_frame, Eigen::VectorXd v); 
        Eigen::MatrixXd skew(const Eigen::VectorXd& v); // Compute the skew symmetric matrix of a vector
        Eigen::VectorXd check_work_limits(const Eigen::VectorXd& v);

        // debug methods
        void printGenericTransformation(const std::string& target_frame, const std::string& source_frame); 
        void debugJointRobot(int jnm, int q, int J, int tfs, int tf_x, const std::string& target_frame, const std::string& source_frame); 
        void debugKukaRobot(int jnm, int q, int J, int tfs, int tf_x, const std::string& target_frame, const std::string& source_frame); 
        void debugUR10eRobot(int jnm, int q, int J, int tfs, int tf_x, const std::string& target_frame, const std::string& source_frame);

        // temporary variables
        Eigen::VectorXd singular_values_;

    private:
        // ------------------------------------ PRIVATE DATA MEMBERS -------------------------------------------------------- //
        std::shared_ptr<KukaRobot> kuka_robot_ = std::make_shared<KukaRobot>();     
        std::shared_ptr<UR10eRobot> ur10_robot_ = std::make_shared<UR10eRobot>();
        std::shared_ptr<rclcpp::Node> node_; // Node for JointRobot  
        
        std::vector<std::string> joint_names_; 
        std::vector<std::string> joint_names_tf_chain; 

        std::string kuka_base_frame_ = "kuka_base_link"; 
        std::string ur10_base_frame_ = "base_link"; 
        std::string ur10_tool_frame_ = "tool0"; 
        std::string kuka_tool_frame_ = "kuka_link_6";

        // control variables
        Eigen::VectorXd cart_err_ = Eigen::VectorXd::Zero(6); // position and orientation error
        std::vector<float> carterr_norm_buff_ = {0.0, 0.0}; 
        float rate_of_change = 0.0;
        int rate_of_change_counter = 0;

        // joint trasformations
        std::vector<Eigen::Affine3d> joint_transforms_;
        Eigen::Affine3d kuka_base_transform_;

        // config parameter
        int init_config_param;
        int jacobian_dim_param;

        // joint jacobian
        Eigen::MatrixXd joint_jacobian_complete_; 
        Eigen::MatrixXd joint_jacobian_slidingUR10_;
        
        // proximity task variables
        std::map<std::string, std::pair<float, Eigen::Vector3d>> proximity_task_points_;

        // publishers and subscribers
        rclcpp::Subscription<uc1_robot_perception::msg::ProximityTaskArray>::SharedPtr proximity_task_subscriber_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr debug_trace_publisher_; // command interface

        // ------------------------------------------------------------------------- Action server members
        RobotInitializationState robot_initialization_state_;
        rclcpp_action::Server<uc1_robot_controllers_interfaces::action::MoveRobot>::SharedPtr move_robot_action_server_;
        std::shared_ptr<TfGoalBroadcaster> goal_frame_broadcaster_; 

        rclcpp_action::GoalResponse   handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const uc1_robot_controllers_interfaces::action::MoveRobot::Goal> goal);

        rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<rclcpp_action::ServerGoalHandle<uc1_robot_controllers_interfaces::action::MoveRobot>> goal_handle);

        void handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<uc1_robot_controllers_interfaces::action::MoveRobot>> goal_handle);
        void execute(const std::shared_ptr<rclcpp_action::ServerGoalHandle<uc1_robot_controllers_interfaces::action::MoveRobot>> goal_handle);
        // ------------------------------------------------------------------------- Action client members
        
        // initial joint positions
        Eigen::VectorXd q_init_; // initial joint positions for both robots
        Eigen::VectorXd kuka_q_init_ = Eigen::VectorXd::Zero(6); 
        Eigen::VectorXd ur10_q_init_ = Eigen::VectorXd::Zero(6); 

        //robot work limits
        double x_lim = 4.5;
        double y_lim = 4.5;
        double z_lim = 4.5;

        // ...............................................................................queste variabili potrebbero essere inutili
        // joint state vectors
        Eigen::VectorXd joint_q_;       // positions
        Eigen::VectorXd joint_q_cmd_;   // command positions

        Eigen::VectorXd joint_ql_upp_;    // upper joint limits
        Eigen::VectorXd joint_ql_low_;    // lower joint limits
        // ...............................................................................queste variabili potrebbero essere inutili
};

#endif // JOINT_ROBOT_HPP
