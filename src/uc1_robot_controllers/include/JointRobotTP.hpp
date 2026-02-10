#ifndef JOINT_ROBOT_TP_HPP
#define JOINT_ROBOT_TP_HPP

// robot interface
#include "RobotInterface.hpp"
#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"

#include "uc1_robot_controllers_interfaces/TPComputation.hpp"
#include "uc1_robot_controllers_interfaces/LowPassFilter.hpp"

// action server
#include "TfGoalBroadcaster.hpp"
#include "uc1_robot_controllers_interfaces/action/move_robot_tp.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "geometry_msgs/msg/point.hpp"
#include "uc1_robot_perception/msg/proximity_task.hpp"
#include "uc1_robot_perception/msg/proximity_task_array.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_action/create_server.hpp"
#include "geometry_msgs/msg/point_stamped.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"

#include "geometry_msgs/msg/transform_stamped.hpp"
#include "std_msgs/msg/string.hpp"

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <cmath>
#include <ctime>

// clocking macro
using Clock = std::chrono::steady_clock;
using us = std::chrono::microseconds;

#define TIC(name) auto name##_start = Clock::now();
#define TOC(name) \
  auto name##_end = Clock::now(); \
  auto name##_dt = std::chrono::duration_cast<us>(name##_end - name##_start).count(); \
  std::cout << #name << ": " << name##_dt << " us\n";

// define frame names
#define KUKA_BASE_LINK "kuka_base_link"
#define KUKA_EE_LINK "kuka_link_6"

#define UR10_BASE_LINK "base_link" // per essere sicuro di considerare tutte le variazioni della transformazione statica kl_6->"ur_base"
#define TOOL "tool0"

// define useful constant
#define NDOF 12

struct tp_task{
    Eigen::MatrixXd RefRate;
    Eigen::MatrixXd ActMatrix;
    Eigen::MatrixXd TskJacobian;
};

// alias definitions
using TasKMapType = std::map<std::string, tp_task>;
using NodeShPtr = rclcpp::Node::SharedPtr;
using MoveRobotTP = uc1_robot_controllers_interfaces::action::MoveRobotTP;

class JointRobotTP
{
    public:
        void initialize(NodeShPtr node_joint_robot, NodeShPtr kuka_node, NodeShPtr ur1o_node);
        void insertInitConfigMap();
        void insertFuncPointerVtc();
        void declareParameters();

        void ReachInitialConfiguration(const std::string init_config_name);
        void RunCartesianReachingLoop(const std::string& goal_frame, bool* reached_goal);
        void SendVelocityCommands(const Eigen::VectorXd& qdot_des, double kuka_gain, double ur10_gain);

        Eigen::Affine3d getGenericTransformation(const std::string& target_frame, const std::string& source_frame);
        Eigen::MatrixXd computePseudoInverse_jointWeight(const Eigen::MatrixXd &jacobian);
        bool sort_prx_task();

        // callbacks
        void proximityTaskCallback(const uc1_robot_perception::msg::ProximityTaskArray::SharedPtr msg);
        void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg);
        void publishArrowMarker(const Eigen::Vector3d& origin, const Eigen::Vector3d& vector, const std::string& frame_id, const std::string& ns, const std::string& color, int id,rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher);

        // ------------------------------------------------- TP TASKS FUNCTIONS ------------------------------------------------- //
        // UPDATER FUNCTIONS
        void UpdateTasksReferenceRate();
        void UpdateTasksActivationFunctions();
        void UpdateTasksJacobians();

        void Update_TRR_JointLimits();
        void Update_TRR_EETarget();
        void Update_TRR_ObstAvoidance();
        void Update_TRR_ObstAvoidance_setBased();
        void Update_TRR_MinAlt();

        void Update_AFunc_JointLimits();
        void Update_AFunc_EETarget();
        void Update_AFunc_ObstAvoidance();
        void Update_AFunc_ObstAvoidance_setBased();
        void Update_AFunc_MinAlt();

        void Update_TskJac_JointLimits();
        void Update_TskJac_EETarget();
        void Update_TskJac_ObstAvoidance();
        void Update_TskJac_ObstAvoidance_setBased();
        void Update_TskJac_MinAlt();
        // ------------------------------------------------- TP TASKS FUNCTIONS ------------------------------------------------- //

        // ------------------------------------------------- LOG VAR ------------------------------------------------- //
        std::vector<Eigen::VectorXd> jl_act, jl_ref, joint_v;
        std::vector<Eigen::VectorXd> obav_act, obav_ref;
        std::vector<Eigen::VectorXd> obav_set_act, obav_set_ref, dist_v;
        std::vector<Eigen::Vector3d> ee_pos, ee_ori, reach_ref_p, reach_ref_o;
        std::vector<Eigen::VectorXd> ee_jacobian;
        std::vector<Eigen::VectorXd> q_dot_vec;
        // ------------------------------------------------- LOG VAR ------------------------------------------------- //
    private:
        // -------------------------------------------------------------------------------------------------------------------------------------------- Robot interfaces
        std::shared_ptr<rclcpp::Node> node_; 
        std::shared_ptr<KukaRobot> kuka_robot_ = std::make_shared<KukaRobot>();     
        std::shared_ptr<UR10eRobot> ur10_robot_ = std::make_shared<UR10eRobot>();
        // -------------------------------------------------------------------------------------------------------------------------------------------- Robot interfaces
        
        // Pub and Sub
        rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr control_task_publisher_;
        rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr point_publisher;
        rclcpp::Subscription<uc1_robot_perception::msg::ProximityTaskArray>::SharedPtr proximity_task_subscriber_;
        rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_states_subscriber_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr debug_trace_publisher_; // utility publisher

        // -------------------------------------------------------------------------------------------------------------------------------------------- Action server
        // members
        std::shared_ptr<TfGoalBroadcaster> goal_frame_broadcaster_;
        rclcpp_action::Server<MoveRobotTP>::SharedPtr move_robot_action_server_;

        rclcpp_action::GoalResponse   handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const MoveRobotTP::Goal> goal);
        rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<rclcpp_action::ServerGoalHandle<MoveRobotTP>> goal_handle);

        // Action server execution methods
        void handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<uc1_robot_controllers_interfaces::action::MoveRobotTP>> goal_handle);
        void execute(const std::shared_ptr<rclcpp_action::ServerGoalHandle<uc1_robot_controllers_interfaces::action::MoveRobotTP>> goal_handle);
        // -------------------------------------------------------------------------------------------------------------------------------------------- Action server

        // -------------------------------------------------------------------------------------------------------------------------------------------- Robot Internal Variables
        // Initial configurations map
        std::map<std::string, Eigen::VectorXd> initial_configurations_map_ = {
            {"default", Eigen::VectorXd::Zero(12)}
        };

        // proximity task variables
        std::mutex proximity_task_mutex_;
        std::vector<uc1_robot_perception::msg::ProximityTask> proximity_task_points_;
        std::vector<uc1_robot_perception::msg::ProximityTask> Prx_task_pts_OBAV_;

        std::map<std::string, uc1_robot_perception::msg::ProximityTask> prx_task_map_;
        uc1_robot_perception::msg::ProximityTask min_dist_task_; 


        // joint states variables
        std::mutex joint_states_mutex_;
        std::map<std::string, double> joint_states_;
        std::map<std::string, double> joint_states_cpy_;

        // TP TASKS VARIABLE
        TasKMapType TP_task_map_;
        // TP Function Pointer Vector
        std::vector<void(JointRobotTP::*)()> TRR_func_vtc;
        std::vector<void(JointRobotTP::*)()> AFunc_func_vtc;
        std::vector<void(JointRobotTP::*)()> TskJac_func_vtc;

        // ============================================== //
        //              experiment logging var            //
        int log_counter_;
        // ============================================== //

        std::vector<double> jl_down_;
        std::vector<double> jl_up_;
         std::vector<double> jl_avg_;
        // -------------------------------------------------------------------------------------------------------------------------------------------- Robot Internal Variables

        // -------------------------------------------------------------------------------------------------------------------------------------------- Frame Names
        std::string goal_name_;
        std::vector<std::string> frame_names_;
        std::vector<std::string> joint_names_;
        // -------------------------------------------------------------------------------------------------------------------------------------------- Frame Names

        // -------------------------------------------------------------------------------------------------------------------------------------------- Parameter definition
        double kuka_gain_;
        double ur10_gain_;
        std::string exp_dir_;
        // -------------------------------------------------------------------------------------------------------------------------------------------- Parameter definition

        // -------------------------------------------------------------------------------------------------------------------------------------------- filter
        LowPassFilter filter_;
        // -------------------------------------------------------------------------------------------------------------------------------------------- filter
};      


#endif // JOINT_ROBOT_TP_HPP