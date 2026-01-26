#include "RobotInterface.hpp"
#include "JointRobotTP.hpp"
#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

// alias definitions
using NodeShPtr = rclcpp::Node::SharedPtr;
using MoveRobotTP = uc1_robot_controllers_interfaces::action::MoveRobotTP;

using namespace std::chrono_literals;
// ------------------------------------------------------------------------------------------------------------------------------- INITIALIZATION METHODS
void JointRobotTP::initialize(NodeShPtr node_joint_robot, NodeShPtr kuka_node, NodeShPtr ur10_node)
{
    // Robot node initialization
    node_ = node_joint_robot;
    // call the each robot init method
    kuka_robot_->initialize(kuka_node);
    ur10_robot_->initialize(ur10_node);

    RCLCPP_INFO(node_->get_logger(), "Robot nodes initialized");

    // Pub e Sub initialization
    debug_trace_publisher_ = node_->create_publisher<std_msgs::msg::String>("debug_trace", 10);
    proximity_task_subscriber_ = node_->create_subscription<uc1_robot_perception::msg::ProximityTaskArray>(
        "/proximity_task_control",
        rclcpp::QoS(10),
        std::bind(&JointRobotTP::proximityTaskCallback, this, std::placeholders::_1)
    );
    joint_states_subscriber_ = node_->create_subscription<sensor_msgs::msg::JointState>(
        "/joint_states",
        rclcpp::QoS(10),
        std::bind(&JointRobotTP::jointStateCallback, this, std::placeholders::_1)
    );
    control_task_publisher_ = node_->create_publisher<visualization_msgs::msg::Marker>("/uc1_viz/control_task", 10);
    goal_frame_broadcaster_ = std::make_shared<TfGoalBroadcaster>(node_);

    point_publisher = node_->create_publisher<geometry_msgs::msg::PointStamped>("debug_point_publisher", 10);

    RCLCPP_INFO(node_->get_logger(), "Pub e Sub initialized");

    // Action server
    move_robot_action_server_ = rclcpp_action::create_server<MoveRobotTP>(
        node_->get_node_base_interface(),
        node_->get_node_clock_interface(),
        node_->get_node_logging_interface(),
        node_->get_node_waitables_interface(),
        "move_robot_tp",

        [this](const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const MoveRobotTP::Goal> goal){
            return this->handle_goal(uuid, goal);
        },

        [this](const std::shared_ptr<rclcpp_action::ServerGoalHandle<MoveRobotTP>> goal_handle){
            return this->handle_cancel(goal_handle);
        },

        [this](const std::shared_ptr<rclcpp_action::ServerGoalHandle<MoveRobotTP>> goal_handle) {
            this->handle_accepted(goal_handle);
        },

        rcl_action_server_get_default_options()
    );
    // populate the init config vectors
    insertInitConfigMap();

    // populate the TP function vectors 
    insertFuncPointerVtc();

    // joint limits vectors
    jl_down_={-3.2, -2.44, -2.0, -6.0, -2.1,-6.0, -6.0, -6.0, -6.0, -6.0, -6.0, -6.0};
    jl_up_ = { 3.2, -0.08,  2.9,  6.0,  2.1, 6.0,  6.0,  6.0,  6.0,  6.0,  6.0,  6.0};
    for(int i=0;i<NDOF;++i){
        jl_avg_.push_back((jl_down_[i]+jl_up_[i])/2);
    }

    frame_names_ = {"kuka_link_1", "kuka_link_2", "kuka_link_3", "kuka_link_4", "kuka_link_5", "kuka_link_6",
                     "shoulder_link", "upper_arm_link", "forearm_link", "wrist_1_link", "wrist_2_link", "wrist_3_link"};

    joint_names_ = {"kuka_joint_a1","kuka_joint_a2","kuka_joint_a3","kuka_joint_a4","kuka_joint_a5","kuka_joint_a6",
                    "shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint", "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"};

    // parameter declaration
    kuka_gain_ = node_->declare_parameter<double>("kuka_gain", 0.05);
    ur10_gain_ = node_->declare_parameter<double>("ur10_gain", 0.5);
    exp_dir_ = node_->declare_parameter<std::string>("exp_dir_name", "def");

    RCLCPP_INFO(node_->get_logger(), "JointRobotTP, initialize complete");
}

void JointRobotTP::insertInitConfigMap(){
    Eigen::VectorXd sing_sing(12);
    sing_sing << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.59, 0.0, -1.59, 0.0, 0.0;

    Eigen::VectorXd zero(12);
    zero << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;

    Eigen::VectorXd sing_mob(12);
    sing_mob << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -3.14159, -2.10757, -1.83066, -0.774163, -1.5708, -0.0300288;

    Eigen::VectorXd mob_sing(12);
    mob_sing << 0.0, 0.785398, -1.578, 0.0, 0.785398, 0.0, 0.0, -1.59, 0.0, -1.59, 0.0, 0.0;
    
    Eigen::VectorXd mob_mob(12);
    mob_mob << 0.0, 0.785398, -1.578, 0.0, 0.785398, 0.0, -3.14159, -2.10757, -1.83066, -0.774163, -1.5708, -0.0300288;

    Eigen::VectorXd stand(12);
    stand << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;

    Eigen::VectorXd good_cnfg(12);
    good_cnfg << 0.0, -2.4, 2.5, 0.0, -0.48, 0.0, 0.0, 0.0, 3.8, 1.35, 1.6, 0.0;

    Eigen::VectorXd free(12);
    free << 0.0, -2.1, 2.4, 0.0, -1.57, 0.0, 0.0, -1.57, 0.0, -1.57, 0.0, 0.0;

    Eigen::VectorXd jl(12);
    jl << 0.0, -1.5, 1.5, 0.0, 1.57, 0.0, 0.0, -1.57, 0.0, -1.57, 0.0, 0.0;

    // insert into the map (DO NOT MODIFY THE DEFAULT CONFIGURATION)
    initial_configurations_map_["jl"] = jl;
    initial_configurations_map_["zero"] = zero;
    initial_configurations_map_["sing_sing"] = sing_sing;
    initial_configurations_map_["sing_mob"] = sing_mob;
    initial_configurations_map_["mob_sing"] = mob_sing;
    initial_configurations_map_["mob_mob"] = mob_mob;
    initial_configurations_map_["stand"] = stand;
    initial_configurations_map_["good_cnfg"] = good_cnfg;
    initial_configurations_map_["free"] = free;
}

void JointRobotTP::insertFuncPointerVtc(){
    //TRR_func_vtc.push_back(&JointRobotTP::Update_TRR_JointLimits);
    TRR_func_vtc.push_back(&JointRobotTP::Update_TRR_EETarget);
    TRR_func_vtc.push_back(&JointRobotTP::Update_TRR_ObstAvoidance);
    TRR_func_vtc.push_back(&JointRobotTP::Update_TRR_ObstAvoidance_setBased);
    //TRR_func_vtc.push_back(&JointRobotTP::Update_TRR_MinAlt);

    //AFunc_func_vtc.push_back(&JointRobotTP::Update_AFunc_JointLimits);
    AFunc_func_vtc.push_back(&JointRobotTP::Update_AFunc_EETarget);
    AFunc_func_vtc.push_back(&JointRobotTP::Update_AFunc_ObstAvoidance);
    AFunc_func_vtc.push_back(&JointRobotTP::Update_AFunc_ObstAvoidance_setBased);
    //AFunc_func_vtc.push_back(&JointRobotTP::Update_AFunc_MinAlt);

    //TskJac_func_vtc.push_back(&JointRobotTP::Update_TskJac_JointLimits);
    TskJac_func_vtc.push_back(&JointRobotTP::Update_TskJac_EETarget);
    TskJac_func_vtc.push_back(&JointRobotTP::Update_TskJac_ObstAvoidance);
    TskJac_func_vtc.push_back(&JointRobotTP::Update_TskJac_ObstAvoidance_setBased);
    //TskJac_func_vtc.push_back(&JointRobotTP::Update_TskJac_MinAlt);

    if(((TRR_func_vtc.size()+AFunc_func_vtc.size()+TskJac_func_vtc.size())%3)!=0){
        RCLCPP_ERROR(node_->get_logger(), "TP FUNCTION VECTOR IS NOT COHERENT, CONTROL DEFINTION");
    }
}
// ------------------------------------------------------------------------------------------------------------------------------- INITIALIZATION METHODS

// ------------------------------------------------------------------------------------------------------------------------------- UPDATER METHODS
void JointRobotTP::UpdateTasksReferenceRate(){
    for(auto func : TRR_func_vtc){
        (this->*func)();
    }
}

void JointRobotTP::UpdateTasksActivationFunctions(){
    for(auto func : AFunc_func_vtc){
        (this->*func)();
    }
}

void JointRobotTP::UpdateTasksJacobians(){
    for(auto func : TskJac_func_vtc){
        (this->*func)();
    }
}
// ------------------------------------------------------------------------------------------------------------------------------- UPDATER METHODS

// ------------------------------------------------------------------------------------------------------------------------------- CALLBACKS METHODS
void JointRobotTP::proximityTaskCallback(const uc1_robot_perception::msg::ProximityTaskArray::SharedPtr msg){
    std::lock_guard<std::mutex> lock(proximity_task_mutex_);
    proximity_task_points_.clear();
    
    for(const auto& task : msg->proximity_tasks){
        if(task.link_id == KUKA_BASE_LINK || task.link_id == UR10_BASE_LINK || task.link_id == "kuka_link_1"){
            continue;
        }else if(proximity_task_points_.size() == 0){
            uc1_robot_perception::msg::ProximityTask prx_task;
            prx_task = task;
            
            proximity_task_points_.push_back(prx_task);
        }else{
            uc1_robot_perception::msg::ProximityTask prx_task;
            prx_task = task;

            if(proximity_task_points_[0].distance > prx_task.distance){
                proximity_task_points_.insert(proximity_task_points_.begin(), prx_task);
            }else{
                proximity_task_points_.push_back(prx_task);
            }
        }
    }

    if(proximity_task_points_.size() != NDOF-1){
        RCLCPP_WARN(node_->get_logger(), "Proximity task points size does not match frame names size!");
    }

    // publish arrow for min dist task
    //double dist = proximity_task_points_[0].distance;
    //Eigen::Vector3d origin(proximity_task_points_[0].min_point_robot.x, proximity_task_points_[0].min_point_robot.y, proximity_task_points_[0].min_point_robot.z);
    //Eigen::Vector3d vector(proximity_task_points_[0].min_point_vector.x*dist, proximity_task_points_[0].min_point_vector.y*dist, proximity_task_points_[0].min_point_vector.z*dist);
    
    //publishArrowMarker(origin, vector, KUKA_BASE_LINK, "min_dist_point", "bblue", 1, control_task_publisher_);
    //std::cout << proximity_task_points_.size() << " --- " << proximity_task_points_[0].distance << " --- " << proximity_task_points_[0].link_id << std::endl;
}

void JointRobotTP::jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg){
    std::lock_guard<std::mutex> lock(joint_states_mutex_);
    
    //joint_var_log.push_back(msg->header.frame_id + "/" + std::to_string(msg->header.stamp.sec)+ "/" + std::to_string(msg->header.stamp.nanosec));

    //std::cout << msg->name.size() << std::endl;
}

void JointRobotTP::publishArrowMarker(
    const Eigen::Vector3d& origin,
    const Eigen::Vector3d& vector,
    const std::string& frame_id,
    const std::string& ns,
    const std::string& color,
    int id,
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher)
{
    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = frame_id;
    marker.header.stamp = node_->get_clock()->now();
    marker.lifetime = rclcpp::Duration(0,0);
    marker.ns = ns;
    marker.id = id;
    marker.type = visualization_msgs::msg::Marker::ARROW;
    marker.action = visualization_msgs::msg::Marker::ADD;

    geometry_msgs::msg::Point start, end;
    start.x = origin.x();
    start.y = origin.y();
    start.z = origin.z();

    end.x = origin.x() + vector.x();
    end.y = origin.y() + vector.y();
    end.z = origin.z() + vector.z();

    marker.points.clear();
    marker.points.push_back(start);
    marker.points.push_back(end);

    marker.scale.x = 0.02;  // shaft diameter
    marker.scale.y = 0.04;  // head diameter
    marker.scale.z = 0.1;   // head length

    marker.color.a = 1.0;
    if(color == "red"){
        marker.color.r = 1.0;
        marker.color.g = 0.0;
        marker.color.b = 0.0;
    } else if(color == "green"){
        marker.color.r = 0.0;
        marker.color.g = 1.0;
        marker.color.b = 0.0;
    } else if(color == "blue"){
        marker.color.r = 0.0;
        marker.color.g = 0.0;
        marker.color.b = 1.0;
    } else if(color == "bblue"){
        marker.color.r = 0.0;
        marker.color.g = 0.58;
        marker.color.b = 1.0;
    } else{
        marker.color.r = 1.0;
        marker.color.g = 1.0;
        marker.color.b = 1.0;
    }

    publisher->publish(marker);
}
// ------------------------------------------------------------------------------------------------------------------------------- CALLBACKS METHODS

// ------------------------------------------------------------------------------------------------------------------------------- MOVEMENT RELATED METHODS
void JointRobotTP::SendVelocityCommands(const Eigen::VectorXd& qdot_des, double kuka_gain, double ur10_gain){
    if(!qdot_des.array().isNaN().any()){
        kuka_robot_->updateJointPositionCommand(kuka_robot_->getJointPositions(),(kuka_gain * qdot_des.head(6))); 
        ur10_robot_->sendJointVelocityCommand(ur10_gain * qdot_des.tail(6));
    } else{
        RCLCPP_WARN(node_->get_logger(), "NaN detected in the velocity command, not sending commands to the robots.");
    }
}

void JointRobotTP::ReachInitialConfiguration(const std::string init_config_name){
    RCLCPP_INFO(node_->get_logger(), "Reaching initial configuration: %s", init_config_name.c_str());
    if(init_config_name == "stand"){
        RCLCPP_WARN(node_->get_logger(), "Robot stand in place.\n");
        kuka_robot_->runJointControlLoop(Eigen::VectorXd::Zero(6), initial_configurations_map_["default"](Eigen::seq(0,5)));
        ur10_robot_->runJointControlLoop(Eigen::VectorXd::Zero(6), initial_configurations_map_["default"](Eigen::seq(6,11)));
    }else if(initial_configurations_map_.find(init_config_name) == initial_configurations_map_.end()){
        RCLCPP_WARN(node_->get_logger(), "Initial configuration name not found, setting default configuration.\n");
        std::cout << initial_configurations_map_["default"].transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        kuka_robot_->runJointControlLoop(Eigen::VectorXd::Ones(6), initial_configurations_map_["default"](Eigen::seq(0,5)));
        ur10_robot_->runJointControlLoop(Eigen::VectorXd::Ones(6), initial_configurations_map_["default"](Eigen::seq(6,11)));
    }else{
        RCLCPP_WARN(node_->get_logger(), "setting configuration.\n");
        std::cout << initial_configurations_map_[init_config_name].transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        kuka_robot_->runJointControlLoop(Eigen::VectorXd::Ones(6), initial_configurations_map_[init_config_name](Eigen::seq(0,5)));
        ur10_robot_->runJointControlLoop(Eigen::VectorXd::Ones(6), initial_configurations_map_[init_config_name](Eigen::seq(6,11)));
    }
}

void JointRobotTP::RunCartesianReachingLoop(const std::string& goal_frame, bool reached_goal){
    rclcpp::Rate loop_rate(50);

    TPComputation tp_controller;

    double kuka_gain, ur10_gain;
    if((node_->has_parameter("kuka_gain") && node_->has_parameter("ur10_gain"))){
        // exp variables
        kuka_gain = kuka_gain_;
        ur10_gain = ur10_gain_;
        RCLCPP_INFO(node_->get_logger(), "\n\n%f %f\n\n, kuka and ur10 gain parameter", kuka_gain_, ur10_gain_);
    }
    
    double lambda = 0.0001; 
    double threshold = 0.01;
    double weight = 10.0;

    std_msgs::msg::String msg;
    msg.data = "ciao";
      

    RCLCPP_WARN(node_->get_logger(), "KUKA gain: %.4f and UR10 gain: %.4f", kuka_gain, ur10_gain);
    while(rclcpp::ok() && !reached_goal){
        // ---------------------- UPDATE DATA STEP ---------------------- //
        UpdateTasksReferenceRate();
        UpdateTasksActivationFunctions();
        UpdateTasksJacobians();
        // ---------------------- UPDATE DATA STEP ---------------------- //

        // ---------------------- Eval STOP CONDION --------------------- //
        Eigen::VectorXd ee_error = TP_task_map_["endeff_target"].RefRate;
        Eigen::VectorXd pos = ee_error.head(3);
        Eigen::VectorXd ang = ee_error.tail(3);
        if(0){
            if(pos.norm() != 0.0 && pos.norm() < 0.03){
                RCLCPP_INFO(node_->get_logger(), "Goal reached with position error: %.4f", pos.norm());
                reached_goal = true;
                continue;
            }else if(ang.norm() != 0.0 && ang.norm() < 0.03){
                RCLCPP_INFO(node_->get_logger(), "Goal reached with orientation error: %.4f", ang.norm());
                reached_goal = true;
                continue;
            }else{
                RCLCPP_INFO(node_->get_logger(), "(%.4f,%.4f)", pos.norm(),ang.norm());
            }
        }else{
            if(ee_error.norm() < 0.03){
                RCLCPP_INFO(node_->get_logger(), "Goal reached with cartesian error: %.4f", ee_error.norm());
                reached_goal = true;
                continue;
            }else{
                //RCLCPP_INFO(node_->get_logger(), "(%.3f,%.3f) - %.4f", pos.norm(),ang.norm(), ee_error.norm());
            }
        }
        // ---------------------- Eval STOP CONDION --------------------- //

        //std::cout << TP_task_map_["obstacle_avoidance_setbased"].ActMatrix.rows() << "-" << TP_task_map_["obstacle_avoidance_setbased"].ActMatrix.cols() << std::endl;
        //std::cout << TP_task_map_["obstacle_avoidance_setbased"].TskJacobian.rows() << "-" << TP_task_map_["obstacle_avoidance_setbased"].TskJacobian.cols() << std::endl;
        //std::cout << TP_task_map_["obstacle_avoidance_setbased"].RefRate.rows() << "-" << TP_task_map_["obstacle_avoidance_setbased"].RefRate.cols() << std::endl;


        // ---------------------- UPDATE TPIK STEP ---------------------- //
        tp_controller.init_TPComputation(NDOF, lambda, threshold, weight); 
        //tp_controller.computeTP_step("joint_limits",  TP_task_map_["joint_limits"].ActMatrix,  TP_task_map_["joint_limits"].TskJacobian,  TP_task_map_["joint_limits"].RefRate);
        //tp_controller.computeTP_step("min_altitude",  TP_task_map_["min_altitude"].ActMatrix,  TP_task_map_["min_altitude"].TskJacobian,  TP_task_map_["min_altitude"].RefRate);
        tp_controller.computeTP_step("obstacle_avoidance",  TP_task_map_["obstacle_avoidance"].ActMatrix,  TP_task_map_["obstacle_avoidance"].TskJacobian,  TP_task_map_["obstacle_avoidance"].RefRate);
        //tp_controller.computeTP_step("obstacle_avoidance_setbased",  TP_task_map_["obstacle_avoidance_setbased"].ActMatrix,  TP_task_map_["obstacle_avoidance_setbased"].TskJacobian,  TP_task_map_["obstacle_avoidance_setbased"].RefRate);
        tp_controller.computeTP_step("endeff_target", TP_task_map_["endeff_target"].ActMatrix, TP_task_map_["endeff_target"].TskJacobian, TP_task_map_["endeff_target"].RefRate);
        tp_controller.computeTP_step("close_task", Eigen::MatrixXd::Identity(NDOF,NDOF), Eigen::MatrixXd::Identity(NDOF,NDOF), Eigen::VectorXd::Zero(NDOF)); 
        Eigen::VectorXd qdot_des = tp_controller.getTP_ydot();
        
        tp_controller.clear_TPComputation();  
        // ---------------------- UPDATE TPIK STEP ---------------------- //


        // ---------------------- SEND VELOCITY STEP -------------------- //
        SendVelocityCommands(qdot_des, kuka_gain, ur10_gain);
        // ---------------------- SEND VELOCITY STEP -------------------- //
        
        // CLEAR TASK PRIORITY MAP -------------------------------------- //
        TP_task_map_.clear();
        // CLEAR TASK PRIORITY MAP -------------------------------------- //

        
        debug_trace_publisher_->publish(msg);

        loop_rate.sleep();
    }
}
// ------------------------------------------------------------------------------------------------------------------------------- MOVEMENT RELATED METHODS

// ------------------------------------------------------------------------------------------------------------------------------- TRASFORMATIONS HANDLING METHODS
Eigen::Affine3d JointRobotTP::getGenericTransformation(const std::string& target_frame, const std::string& source_frame){
    // using the wrapper to avoid the heaviness of the sintax
    return kuka_robot_->getGenericTransformation(target_frame, source_frame);
}

Eigen::MatrixXd JointRobotTP::computePseudoInverse_jointWeight(const Eigen::MatrixXd &jacobian)
{
    double mu = 0.1;

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(jacobian, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::MatrixXd SigmaPlus(jacobian.cols(), jacobian.rows());
    Eigen::MatrixXd Weights = Eigen::MatrixXd::Identity(jacobian.cols(), jacobian.cols());
    Eigen::VectorXd eigen = svd.singularValues();

    for(int i=0; i<jacobian.cols(); ++i){
        Weights(i,i) = 1.0;
    }

    int r = eigen.size();
    SigmaPlus.setZero();
    // for singular values equal to 0
    for (int i = 0; i < r; i++)
    {
        SigmaPlus(i, i) = eigen(i) / (eigen(i) * eigen(i) + mu * mu);
    }
    // std::cout << SigmaPlus << "\n\n";

    Eigen::MatrixXd V = svd.matrixV();
    Eigen::MatrixXd UT = svd.matrixU().transpose().eval();

    std::cout << "joint weights:\n" << std::setprecision(2) << Weights.diagonal().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
    return V * Weights * SigmaPlus * UT;
}
// ------------------------------------------------------------------------------------------------------------------------------- TRASFORMATIONS HANDLING METHODS

// ------------------------------------------------------------------------------------------------------------------------------- ACTION SERVER
rclcpp_action::GoalResponse JointRobotTP::handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const MoveRobotTP::Goal> goal){
    (void)uuid;
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse JointRobotTP::handle_cancel(const std::shared_ptr<rclcpp_action::ServerGoalHandle<MoveRobotTP>> goal_handle){
    (void)goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
}

void JointRobotTP::handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<MoveRobotTP>> goal_handle){
    using namespace std::placeholders;

    std::thread{std::bind(&JointRobotTP::execute, this, _1), goal_handle}.detach();
}

void JointRobotTP::execute(const std::shared_ptr<rclcpp_action::ServerGoalHandle<MoveRobotTP>> goal_handle){
    // resolve the goal handle, get the target and other info
    const auto goal = goal_handle->get_goal();
    auto feedback = std::make_shared<MoveRobotTP::Feedback>();
    auto result = std::make_shared<MoveRobotTP::Result>();

    // check goal cancellation
    if(goal_handle->is_canceling()){
        result->result = "Goal cancelled by user";
        goal_handle->canceled(result);
        return;
    }

    // ---------------------------------------------------------------------------------------------------------- INITIAL CONFIGURATION REACHING
    // The initi config is a string, the string is used as key in a map to get the corresponging joint var vector
    const std::string init_config_param = goal->init_config_name;
    ReachInitialConfiguration(init_config_param);
    // ---------------------------------------------------------------------------------------------------------- INITIAL CONFIGURATION REACHING

    std::this_thread::sleep_for(500ms);

    // dump delle trasformazioni nel commento sotto
    /*
    // print trasformation sequence
    Eigen::Affine3d temp;
    std::cout << "---------------------------------------" << std::endl;
    for(int i=0;i<NDOF;++i){
        temp = getGenericTransformation(KUKA_BASE_LINK, frame_names_[i]);
        std::cout << "frame: " << frame_names_[i] << std::endl;
        std::cout << std::fixed << std::setprecision(3);
        std::cout << temp.matrix() << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl;
    temp = getGenericTransformation(KUKA_BASE_LINK, frame_names_[0]);
    std::cout << "frame: " << frame_names_[0] << std::endl;
    std::cout << std::fixed << std::setprecision(3);
    std::cout << temp.matrix() << std::endl;
    for(int i=0;i<NDOF;++i){
        if(i==NDOF-1){
            temp = getGenericTransformation(frame_names_[i], frame_names_[i]);
        }else{
            temp = getGenericTransformation(frame_names_[i], frame_names_[i+1]);
        }
        std::cout << "frame: " << frame_names_[i] << std::endl;
        std::cout << std::fixed << std::setprecision(3);
        std::cout << temp.matrix() << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl;
    temp = getGenericTransformation(KUKA_BASE_LINK, "base_link");
    std::cout << "frame: " << "{{{base_link}}}" << std::endl;
    std::cout << std::fixed << std::setprecision(3);
    std::cout << temp.matrix() << std::endl;

    std::cout << "---------------------------------------" << std::endl;
    temp = getGenericTransformation("base_link_inertia", "shoulder_link");
    std::cout << "frame: " << "[{{shoulder_link}}]" << std::endl;
    std::cout << std::fixed << std::setprecision(3);
    std::cout << temp.matrix() << std::endl;

    std::cout << "---------------------------------------" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    temp = getGenericTransformation(KUKA_BASE_LINK, "kuka_link_1");
    std::cout << "frame: " << KUKA_BASE_LINK << "--" << "kuka_link_1" << std::endl;
    std::cout << std::fixed << std::setprecision(3);
    std::cout << temp.matrix() << std::endl;
    for(int i=0;i<NDOF/2;++i){
        temp = getGenericTransformation(frame_names_[i], frame_names_[i+1]);
        std::cout << "frame: " << frame_names_[i] << "--" << frame_names_[i+1] << std::endl;
        std::cout << std::fixed << std::setprecision(3);
        std::cout << temp.matrix() << std::endl;
    }
    temp = getGenericTransformation("base_link", "shoulder_link");
    std::cout << "frame: " << "base_link" << "--" << "shoulder_link" << std::endl;
    std::cout << std::fixed << std::setprecision(3);
    std::cout << temp.matrix() << std::endl;
    for(int i=6;i<NDOF;++i){
        if(i==NDOF-1){
            temp = getGenericTransformation(frame_names_[i], frame_names_[i]);
            std::cout << "frame: " << frame_names_[i] << "--" << frame_names_[i] << std::endl;
        }else{
            temp = getGenericTransformation(frame_names_[i], frame_names_[i+1]);
            std::cout << "frame: " << frame_names_[i] << "--" << frame_names_[i+1] << std::endl;
        }
        std::cout << std::fixed << std::setprecision(3);
        std::cout << temp.matrix() << std::endl;
    }
    */


    // ---------------------------------------------------------------------------------------------------------- GOAL FRAME BROADCASTING
    Eigen::VectorXd goal_req_trals(3);
    Eigen::VectorXd goal_req_rotat(3);

    goal_req_trals << goal->goal.translation.x, goal->goal.translation.y, goal->goal.translation.z;
    goal_req_rotat << goal->goal.orientation.roll, goal->goal.orientation.pitch, goal->goal.orientation.yaw; 

    // convert goal request in a RPY matrix
    Eigen::MatrixXd Rz, Ry, Rx;
    Eigen::Matrix3d R_goal;
    Rz = Eigen::AngleAxisd(goal_req_rotat[2], Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Ry = Eigen::AngleAxisd(goal_req_rotat[1], Eigen::Vector3d::UnitY()).toRotationMatrix();
    Rx = Eigen::AngleAxisd(goal_req_rotat[0], Eigen::Vector3d::UnitX()).toRotationMatrix();
    R_goal = Rz * Ry * Rx;

    // goal translation in the kuka base frame
    Eigen::VectorXd goal_traslation(3);
    Eigen::VectorXd goal_rotation(3);

    Eigen::Affine3d kuka_tool = getGenericTransformation(KUKA_BASE_LINK, TOOL);

    goal_traslation = goal_req_trals + kuka_tool.translation();

    Eigen::Matrix3d fxd_prj = kuka_tool.linear(); // rotation matrix from ur10_tool to kuka_ee
    goal_rotation = (fxd_prj * R_goal).eulerAngles(2, 1, 0);

    // define broadcast frames of the goal frame
    std::string parent_frame = KUKA_BASE_LINK;
    std::string goal_frame  = "GOAL_FRAME";
    goal_name_ = goal_frame;

    //goal_traslation << 1.8131, 0.0, 2.0592;
    //goal_traslation << 0.5, 0.0, 0.5; 
    goal_rotation << 0.0, 0.0, 0.0;

    goal_frame_broadcaster_->broadcastStaticTransform(goal_traslation, goal_rotation.reverse(), parent_frame, goal_frame);
    std::cout << "Goal sent (position): " << goal_traslation.transpose() << std::endl;
    std::cout << "Goal sent (orientat): " << goal_rotation.transpose() << std::endl;
    std::cout << "Pr frame:" << parent_frame << ", Gl frame:" << goal_frame << std::endl; 
    // ---------------------------------------------------------------------------------------------------------- GOAL FRAME BROADCASTING

    // ---------------------------------------------------------------------------------------------------------- EXECUTE REACHING LOOP
    std::this_thread::sleep_for(1000ms);
    std::cout << "\nSTARTNG REACHING LOOP" << std::endl;

    
    bool reached_goal = false;
    RunCartesianReachingLoop(goal_frame, reached_goal);

    
    // ---------------------------------------------------------------------------------------------------------- EXECUTE REACHING LOOP

    // ---------------------------------------------------------------------------------------------------------- LOG RESULT ON FILE
    std::string path = "/home/maclab/Documents/ROS_WORKSPACES/experiment";
    std::string slash = "/";
    std::string dir = slash + exp_dir_;
    // JOINT LIMITS
    std::ofstream jl_act_log = std::ofstream(path + dir + "/jl_act_log.txt", std::ios::app);
    if(jl_act_log.is_open()){
        for(int i=0; i<jl_act.size(); ++i){
            jl_act_log << jl_act[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }

    std::ofstream jl_ref_log = std::ofstream(path + dir + "/jl_ref_log.txt", std::ios::app);
    if(jl_ref_log.is_open()){
        for(int i=0; i<jl_ref.size(); ++i){
            jl_ref_log << jl_ref[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }

    std::ofstream joint_v_log = std::ofstream(path + dir + "/joint_v_log.txt", std::ios::app);
    if(joint_v_log.is_open()){
        for(int i=0; i<joint_v.size(); ++i){
            joint_v_log << joint_v[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }
    
    // OBSTACLE AVOIDANCE NORMAL
    std::ofstream obav_act_log = std::ofstream(path + dir + "/obav_act_log.txt", std::ios::app);
    if(obav_act_log.is_open()){
        for(int i=0; i<obav_act.size(); ++i){
            obav_act_log << obav_act[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }

    std::ofstream obav_ref_log = std::ofstream(path + dir + "/obav_ref_log.txt", std::ios::app);
    if(obav_ref_log.is_open()){
        for(int i=0; i<obav_ref.size(); ++i){
            obav_ref_log << obav_ref[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }
    
    // OBSTACLE AVOIDANCE SET BASED
    std::ofstream obav_set_act_log = std::ofstream(path + dir + "/obav_set_act_log.txt", std::ios::app);
    if(obav_set_act_log.is_open()){
        for(int i=0; i<obav_set_act.size(); ++i){
            obav_set_act_log << obav_set_act[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }

    std::ofstream obav_set_ref_log = std::ofstream(path + dir + "/obav_set_ref_log.txt", std::ios::app);
    if(obav_set_ref_log.is_open()){
        for(int i=0; i<obav_set_ref.size(); ++i){
            obav_set_ref_log << obav_set_ref[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }

    std::ofstream dist_v_log = std::ofstream(path + dir + "/dist_v_log.txt", std::ios::app);
    if(dist_v_log.is_open()){
        for(int i=0; i<dist_v.size(); ++i){
            dist_v_log << dist_v[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }

    // REACHING TASK
    std::ofstream ee_pos_log = std::ofstream(path + dir + "/ee_pos_log.txt", std::ios::app);
    if(ee_pos_log.is_open()){
        for(int i=0; i<ee_pos.size(); ++i){
            ee_pos_log << ee_pos[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }

    std::ofstream ee_ori_log = std::ofstream(path + dir + "/ee_ori_log.txt", std::ios::app);
    if(ee_ori_log.is_open()){
        for(int i=0; i<ee_ori.size(); ++i){
            ee_ori_log << ee_ori[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }

    std::ofstream reach_ref_p_log = std::ofstream(path + dir + "/reach_ref_p_log.txt", std::ios::app);
    if(reach_ref_p_log.is_open()){
        for(int i=0; i<reach_ref_p.size(); ++i){
            reach_ref_p_log << reach_ref_p[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }

    std::ofstream reach_ref_o_log = std::ofstream(path + dir + "/reach_ref_o_log.txt", std::ios::app);
    if(reach_ref_o_log.is_open()){
        for(int i=0; i<reach_ref_o.size(); ++i){
            reach_ref_o_log << reach_ref_o[i].reshaped().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
        }  
    }


    // ---------------------------------------------------------------------------------------------------------- LOG RESULT ON FILE


    if(rclcpp::ok()){
        result->result = "Reaching Loop completed, ready for next Goal\n";
        goal_handle->succeed(result);
    }
}
// ------------------------------------------------------------------------------------------------------------------------------- ACTION SERVER
