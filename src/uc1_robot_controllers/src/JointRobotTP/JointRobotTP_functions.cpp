#include "RobotInterface.hpp"
#include "JointRobotTP.hpp"
#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

// alias definitions
using NodeShPtr = rclcpp::Node::SharedPtr;
using MoveRobotTP = uc1_robot_controllers_interfaces::action::MoveRobotTP;

using namespace std::chrono_literals;

// IN THIS FILE I WILL DEFINE ALL THE METHODS THAT I USE FOR THE TP ALGO
// --------------------------------------------------------------------- TASK REFERENCE
void JointRobotTP::Update_TRR_JointLimits(){
    //RCLCPP_INFO(node_->get_logger(), "--- [Update TRR JointLimits] ---");

    tp_task task;
    TP_task_map_["joint_limits"] = task;

    Eigen::VectorXd kuka_q = kuka_robot_->getJointPositions();
    Eigen::VectorXd ur10_q = ur10_robot_->getJointPositions();
    int kuka_sz = kuka_q.size();
    int ur10_sz = ur10_q.size();

    if((kuka_sz+ur10_sz) == NDOF){
        // instantiate after for initializing the dimenision
        TP_task_map_["joint_limits"].RefRate.resize((kuka_sz+ur10_sz),1);
        TP_task_map_["joint_limits"].RefRate.block(0,0,kuka_sz,1) = kuka_q;
        TP_task_map_["joint_limits"].RefRate.block(kuka_sz,0,ur10_sz,1) = ur10_q;

        //SAVE LOG VAR
        joint_v.push_back(TP_task_map_["joint_limits"].RefRate);
        //SAVE LOG VAR

        double jl_gain = node_->get_parameter("jl_gain_ref_rat").as_double();
        for(int i=0; i<NDOF; ++i){
            if(TP_task_map_["joint_limits"].RefRate(i) <= jl_avg_[i]){
                TP_task_map_["joint_limits"].RefRate(i) = jl_gain * (abs(jl_avg_[i]-TP_task_map_["joint_limits"].RefRate(i))+0.01);
            }else{
                TP_task_map_["joint_limits"].RefRate(i) = -jl_gain * (abs(jl_avg_[i]-TP_task_map_["joint_limits"].RefRate(i))-0.01);
            }
        }

        //SAVE LOG VAR
        jl_ref.push_back(TP_task_map_["joint_limits"].RefRate);
        //SAVE LOG VAR

    }else{
        //RCLCPP_ERROR(node_->get_logger(), "JOINT LIMITS Tsk Ref DIM ERROR");
    }
}

void JointRobotTP::Update_TRR_EETarget(){
    //RCLCPP_INFO(node_->get_logger(), "--- [Update TRR EETarget] ---");

    tp_task task;
    TP_task_map_["endeff_target"] = task;

    Eigen::Affine3d goal_tf = getGenericTransformation(KUKA_BASE_LINK, goal_name_); // tf from kuka_base to goal_frame
    Eigen::Affine3d tool_tf = getGenericTransformation(KUKA_BASE_LINK, TOOL);       // tf from kuka_base to tool0

    Eigen::VectorXd cart_err = kuka_robot_->computeCartesianReachingTask(goal_tf, tool_tf);

    geometry_msgs::msg::PointStamped msg;
    msg.header.frame_id = "tool";
    msg.point.x = (tool_tf.translation())(0);
    msg.point.y = (tool_tf.translation())(1);
    msg.point.z = (tool_tf.translation())(2);
    point_publisher->publish(msg);

    /// SAVE LOG VAR
    ee_pos.push_back(Eigen::Vector3d((tool_tf.translation())(0),(tool_tf.translation())(1),(tool_tf.translation())(2)));
    ee_ori.push_back(Eigen::Vector3d((tool_tf.linear().eulerAngles(2, 1, 0).reverse())));
    reach_ref_p.push_back(Eigen::Vector3d(cart_err[0],cart_err[1],cart_err[2]));
    reach_ref_o.push_back(Eigen::Vector3d(cart_err[3],cart_err[4],cart_err[5]));
    /// SAVE LOG VAR

    double lin_gain = node_->get_parameter("eer_lin_gain").as_double();
    double ori_gain = node_->get_parameter("eer_ori_gain").as_double();
    cart_err.head(3) = cart_err.head(3) * lin_gain;
    cart_err.tail(3) = cart_err.tail(3) * ori_gain;

    // test temp: remove error from rotation part
    //cart_err.tail(3) = Eigen::Vector3d::Zero();

    TP_task_map_["endeff_target"].RefRate.resize(cart_err.size(), 1);
    TP_task_map_["endeff_target"].RefRate.block(0,0,cart_err.size(),1) = cart_err;

    //std::cout << "EE Target Ref Rate: " << TP_task_map_["endeff_target"].RefRate.transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
    //publishArrowMarker(Eigen::Vector3d((tool_tf.translation())(0),(tool_tf.translation())(1),(tool_tf.translation())(2)),
    //                   Eigen::Vector3d(cart_err[0],cart_err[1],cart_err[2]),
    //                    KUKA_BASE_LINK, "reach_ref", "red", 1, control_task_publisher_);
}

void JointRobotTP::Update_TRR_ObstAvoidance(){
    // copy point map in place holder variable
    Prx_task_pts_OBAV_.clear();
    std::lock_guard<std::mutex> lock(proximity_task_mutex_);
    Prx_task_pts_OBAV_ = proximity_task_points_;

    if(min_dist_task_.distance > Prx_task_pts_OBAV_[0].distance+node_->get_parameter("prx_task_trsh").as_double()){
        min_dist_task_ = Prx_task_pts_OBAV_[0];
    }else{
        for(int i=0;i<Prx_task_pts_OBAV_.size();++i){
            if(min_dist_task_.link_id == Prx_task_pts_OBAV_[i].link_id){
                min_dist_task_ = Prx_task_pts_OBAV_[i];
                break;
            }
        }
        Prx_task_pts_OBAV_[0] = min_dist_task_;
    }

    // create new task, save in map, save insertion result
    std::string task_name = "obstacle_avoidance";
    tp_task task;
    std::pair<TasKMapType::iterator, bool> insResult;
    insResult = TP_task_map_.insert({task_name, task});

    // progressive check list of information
    Eigen::Vector2d filt_vector;
    Eigen::Vector3d origin, vector;
    if(!Prx_task_pts_OBAV_.empty()){ // check for at least 1 min dist points (look out for missing messages publised)
        filt_vector = Eigen::Vector2d(
            -Prx_task_pts_OBAV_[0].min_point_vector.x,
            -Prx_task_pts_OBAV_[0].min_point_vector.y
            //-Prx_task_pts_OBAV_[0].min_point_vector.z
        );
        TP_task_map_[task_name].RefRate = filt_vector;
        origin << Prx_task_pts_OBAV_[0].min_point_robot.x, Prx_task_pts_OBAV_[0].min_point_robot.y, Prx_task_pts_OBAV_[0].min_point_robot.z;
        vector << -Prx_task_pts_OBAV_[0].min_point_vector.x, -Prx_task_pts_OBAV_[0].min_point_vector.y, -Prx_task_pts_OBAV_[0].min_point_vector.z; 
    }

    /// SAVE LOG VAR
    Eigen::VectorXd vec(3); 
    vec(0) = TP_task_map_[task_name].RefRate(0); 
    vec(1) = TP_task_map_[task_name].RefRate(1); 
    //vec(2) = TP_task_map_[task_name].RefRate(2); 
    obav_ref.push_back(vec); 
    /// SAVE LOG VAR
    std::cout << "[OBV REF RT](nrm/filt):\n" << Prx_task_pts_OBAV_[0].link_id << " // " << Prx_task_pts_OBAV_[0].distance << "\n" << 
                                                min_dist_task_.link_id << " // " << min_dist_task_.distance << "\n" << std::endl;
    //std::cout << "[OBV REF RT](nrm/filt):\n" << vector.transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << "(" << vector.norm() << ")" << "/" << filt_vector.transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << "(" << filt_vector.norm() << ")" << std::endl;
    //std::cout << "[UPDATE TRR] OBAV Ref Rate: " << TP_task_map_["obstacle_avoidance"].RefRate.rows() << "." << TP_task_map_["obstacle_avoidance"].RefRate.cols() << std::endl;
    //std::cout << "[UPDATE TRR] OBAV Ref Rate: " << TP_task_map_["obstacle_avoidance"].RefRate.transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
    //publishArrowMarker(origin, vector, KUKA_BASE_LINK, "obst_avoidance", "red", 1, control_task_publisher_);
    //publishArrowMarker(origin, filt_vector, KUKA_BASE_LINK, "obst_avoidance_filtered", "blue", 1, control_task_publisher_);
}

void JointRobotTP::Update_TRR_ObstAvoidance_setBased(){
    std::string task_name = "obstacle_avoidance_setbased";
    tp_task task;

    TP_task_map_[task_name] = task;
    TP_task_map_[task_name].RefRate.resize(frame_names_.size(),1);
    Eigen::VectorXd dist_raw = Eigen::VectorXd::Zero(frame_names_.size());

    double obv_set_gain = node_->get_parameter("obv_set_gain").as_double();
    double obv_set_min_dist = node_->get_parameter("obv_set_min_dist").as_double();
    double obv_set_delta = node_->get_parameter("obv_set_delta").as_double();
    
    if((TP_task_map_.find("obstacle_avoidance") == TP_task_map_.end())){ // if normal_obav not present -> safe copy of prox task
        Prx_task_pts_OBAV_.clear();
        std::lock_guard<std::mutex> lock(proximity_task_mutex_);
        Prx_task_pts_OBAV_ = proximity_task_points_;
    }

    for(int i=0; i<frame_names_.size(); ++i){               // first loop on frame_names --> RefRate ordinato come frame_names_
        for(int j=0; j<Prx_task_pts_OBAV_.size(); j++){     // second loop on Prx_task (copy)
            if(frame_names_[i] == Prx_task_pts_OBAV_[j].link_id){
                TP_task_map_[task_name].RefRate(i) = obv_set_gain * (obv_set_min_dist + obv_set_delta - Prx_task_pts_OBAV_[j].distance);
                dist_raw(i) = Prx_task_pts_OBAV_[j].distance;
            }
        }
    }

    // to be added 
    obav_set_ref.push_back(TP_task_map_[task_name].RefRate);
    dist_v.push_back(dist_raw);
    // save log var

    //std::cout << TP_task_map_[task_name].RefRate << std::endl;
}

void JointRobotTP::Update_TRR_MinAlt(){
    //RCLCPP_INFO(node_->get_logger(), "--- [Update TRR MinAlt] ---");

    tp_task task;
    TP_task_map_["min_altitude"] = task;

    Eigen::Affine3d tool_tf = getGenericTransformation(KUKA_BASE_LINK, TOOL);       // tf from kuka_base to tool0
    double current_altitude = tool_tf.translation().z();

    double lambda = 0.5;
    double height_limit = 0.30;
    double delta = 0.10;
    TP_task_map_["min_altitude"].RefRate.resize(6, 1);
    TP_task_map_["min_altitude"].RefRate(2,0) = lambda * (height_limit + delta - current_altitude);
    //std::cout << "Ref rate: " << TP_task_map_["min_altitude"].RefRate(0,0) << " Cur Alt: "<< current_altitude << std::endl;
}
// --------------------------------------------------------------------- TASK REFERENCE
////////////////////////////////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- ACTIVATION FUNCTION
void JointRobotTP::Update_AFunc_JointLimits(){
    //RCLCPP_INFO(node_->get_logger(), "--- [Update ACT FUNC Joint Limits] ---");

    // activation function matrix
    int RefRate_sz = TP_task_map_["joint_limits"].RefRate.size();
    TP_task_map_["joint_limits"].ActMatrix = Eigen::MatrixXd::Zero(RefRate_sz, RefRate_sz);

    Eigen::VectorXd joint_v;
    joint_v.resize(RefRate_sz);
    //joint_v.setZero();
    joint_v.head(RefRate_sz/2) = kuka_robot_->getJointPositions();
    joint_v.tail(RefRate_sz/2) = ur10_robot_->getJointPositions();
    
    double jl_act_delta = node_->get_parameter("jl_act_delta").as_double();

    // compute the activation funtion for each joint
    for (int i=0; i<RefRate_sz; ++i){
        double incBellVal = ur10_robot_->IncreasingBellShapedFunction(jl_up_[i]-jl_act_delta,jl_up_[i],0.0,1.0, joint_v[i]);
        double decBellVal = ur10_robot_->DecreasingBellShapedFunction(jl_down_[i],jl_down_[i]+jl_act_delta,0.0,1.0, joint_v[i]);

        TP_task_map_["joint_limits"].ActMatrix(i,i) = incBellVal + decBellVal;
    }

    //SAVE LOG VAR
    jl_act.push_back(Eigen::MatrixXd(TP_task_map_["joint_limits"].ActMatrix.diagonal()));
    //SAVE LOG VAR
}

void JointRobotTP::Update_AFunc_EETarget(){
    //RCLCPP_INFO(node_->get_logger(), "--- [Update ACT FUNC EE Target] ---");


    int RefRate_sz = TP_task_map_["endeff_target"].RefRate.size();
    TP_task_map_["endeff_target"].ActMatrix = Eigen::MatrixXd::Identity(RefRate_sz, RefRate_sz);
}

void JointRobotTP::Update_AFunc_ObstAvoidance(){
    //RCLCPP_INFO(node_->get_logger(), "--- [Update ACT FUNC Obst Avoidance] ---");

    int RefRate_sz = TP_task_map_["obstacle_avoidance"].RefRate.size();
    TP_task_map_["obstacle_avoidance"].ActMatrix = Eigen::MatrixXd::Zero(RefRate_sz, RefRate_sz);

    double obv_dist_limit = node_->get_parameter("obv_dist_limit").as_double();
    double obv_delta = node_->get_parameter("obv_delta").as_double();

    double act_value = 0.0;
    double distance = Prx_task_pts_OBAV_[0].distance;
    //Eigen::Vector3d dir(Prx_task_pts_OBAV_[0].min_point_vector.x, Prx_task_pts_OBAV_[0].min_point_vector.y, Prx_task_pts_OBAV_[0].min_point_vector.z);
    for(int i=0; i<RefRate_sz; ++i){
        act_value = ur10_robot_->DecreasingBellShapedFunction(obv_dist_limit, obv_dist_limit+obv_delta, 0.0, 1.0, distance);
        TP_task_map_["obstacle_avoidance"].ActMatrix(i,i) = act_value;
    }
    
    /// SAVE LOG VAR
    obav_act.push_back(TP_task_map_["obstacle_avoidance"].ActMatrix.diagonal());
    /// SAVE LOG VAR

    //std::cout << "OBAV Ref Rate:\n(" << TP_task_map_["obstacle_avoidance"].RefRate.transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << ") -- (" <<  dir.transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << ") -- " << TP_task_map_["obstacle_avoidance"].RefRate.norm() <<  std::endl;
    //std::cout << "Distance OBAV: " << distance << " -- dir: " << dir.transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", ""));
    //std::cout << "OBAV Act Func:\n" << TP_task_map_["obstacle_avoidance"].ActMatrix.matrix() << std::endl;
    //std::cout << "[UPDATE ACT] OBAV Ref Rate: " << TP_task_map_["obstacle_avoidance"].ActMatrix.rows() << "." << TP_task_map_["obstacle_avoidance"].ActMatrix.cols() << std::endl;
    //std::cout << "[UPDATE ACT] OBAV Ref Rate: " << TP_task_map_["obstacle_avoidance"].RefRate.transpose().format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
}

void JointRobotTP::Update_AFunc_ObstAvoidance_setBased(){
    std::string task_name = "obstacle_avoidance_setbased";
    int RefR_sz = TP_task_map_[task_name].RefRate.size();
    TP_task_map_[task_name].ActMatrix = Eigen::MatrixXd::Zero(RefR_sz, RefR_sz);

    double obv_set_dist_limit = node_->get_parameter("obv_set_dist_limit").as_double();
    double obv_set_delta = node_->get_parameter("obv_set_act_delta").as_double();

    for(int i=0; i<frame_names_.size(); ++i){               // first loop on frame_names --> RefRate ordinato come frame_names_
        for(int j=0; j<Prx_task_pts_OBAV_.size(); j++){     // second loop on Prx_task (copy)
            if(frame_names_[i] == Prx_task_pts_OBAV_[j].link_id){
                TP_task_map_[task_name].ActMatrix(i,i) = ur10_robot_->DecreasingBellShapedFunction(obv_set_dist_limit, obv_set_dist_limit+obv_set_delta, 
                                                                                                   0.0, 1.0, 
                                                                                                   Prx_task_pts_OBAV_[j].distance);
            }
        }
    }

    // log var save
    obav_set_act.push_back(TP_task_map_[task_name].ActMatrix.diagonal());
    // log var save

    //std::cout << TP_task_map_[task_name].ActMatrix.diagonal() << std::endl;
}

void JointRobotTP::Update_AFunc_MinAlt(){
    //RCLCPP_INFO(node_->get_logger(), "--- [Update ACT FUNC Min Altitude] ---");
    double height_limit = 0.30;
    double delta = 0.10;

    int ActFc_sz = TP_task_map_["min_altitude"].RefRate.rows();
    TP_task_map_["min_altitude"].ActMatrix = Eigen::MatrixXd::Zero(ActFc_sz, ActFc_sz);

    Eigen::Affine3d tool_tf = getGenericTransformation(KUKA_BASE_LINK, TOOL);       // tf from kuka_base to tool0
    double current_altitude = tool_tf.translation().z();

    double act_value = ur10_robot_->DecreasingBellShapedFunction(height_limit, height_limit+delta, 0.0, 1.0, current_altitude);
    TP_task_map_["min_altitude"].ActMatrix(2,2) = act_value;
    //std::cout << "Act Func Min Alt: " << act_value << std::endl;
}
// --------------------------------------------------------------------- ACTIVATION FUNCTION
///////////////////////////////////UR10_BASE_LINK/////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- TASK JACOBIAN
void JointRobotTP::Update_TskJac_JointLimits(){
    //RCLCPP_INFO(node_->get_logger(), "--- [Update TASK PosJac Joint Limits] ---");


    int RefRate_sz = TP_task_map_["joint_limits"].RefRate.size();
    TP_task_map_["joint_limits"].TskJacobian = Eigen::MatrixXd::Identity(RefRate_sz, RefRate_sz);
}

void JointRobotTP::Update_TskJac_EETarget(){

    // // compute the Jacobian in the respective base frames
    // Eigen::MatrixXd Jacobian = Eigen::MatrixXd::Zero(6,12);
    // Eigen::MatrixXd J_kuka = kuka_robot_->computeJacobian(KUKA_EE_LINK); // kuka_base__J__6/0
    // Eigen::MatrixXd J_ur10 = ur10_robot_->computeJacobian(TOOL);         // ur10_base__J__6/0  "shoulder_link"
    // // compute the trasformation for projecting ur10 jacobian in kuka base frame
    // Eigen::MatrixXd ur10_projector = getGenericTransformation(KUKA_BASE_LINK, UR10_BASE_LINK).linear();               // kuka_base__R__ur10_base 
    // Eigen::VectorXd ur10_tot_trasl = getGenericTransformation(UR10_BASE_LINK, TOOL).translation();      // ur10_base__r__tool
    // // PROVARE SOSTITUIRE IL SH-LINK AL POSTO DI UR10 BASE LINK
    // Eigen::MatrixXd kukaProj = Eigen::MatrixXd::Identity(6,6);
    // Eigen::MatrixXd ur10Proj = Eigen::MatrixXd::Identity(6,6);

    // ur10Proj.block(0,0,3,3) = ur10_projector;
    // ur10Proj.block(3,3,3,3) = ur10_projector;

    // Eigen::MatrixXd skew_mat = Eigen::MatrixXd::Zero(3,3);
    // Eigen::VectorXd r = ur10_projector * ur10_tot_trasl; 
    // skew_mat << 0,-r(2),r(1),r(2),0,-r(0),-r(1),r(0),0;
    // kukaProj.block(0,3,3,3) = skew_mat.transpose();

    // Jacobian.leftCols(6) = kukaProj * J_kuka;
    // Jacobian.rightCols(6) = ur10Proj * J_ur10;

    // provo a compilare la JACOBIANA con il metodo classico
    Eigen::Affine3d cur_lnk_tf;
    Eigen::Affine3d fixed = getGenericTransformation(KUKA_BASE_LINK, UR10_BASE_LINK);
    Eigen::Affine3d ee_tf = getGenericTransformation(KUKA_BASE_LINK, TOOL);
    Eigen::Vector3d ax_vtc;

    Eigen::MatrixXd urJac = Eigen::MatrixXd::Zero(6,6);
    TP_task_map_["endeff_target"].TskJacobian = Eigen::MatrixXd::Zero(6,NDOF);
    //std::cout << " ///// " << std::endl;

    for(int i=0; i<NDOF; ++i){
        cur_lnk_tf = getGenericTransformation(KUKA_BASE_LINK, frame_names_[i]);
        switch(i){
            case 0: ax_vtc <<0,0,-1; break;
            case 1: ax_vtc <<0,1,0; break;
            case 2: ax_vtc <<0,1,0; break;
            case 3: ax_vtc <<-1,0,0; break;
            case 4: ax_vtc <<0,1,0; break;
            case 5: ax_vtc <<-1,0,0; break;
            case 6: ax_vtc <<0,0,1; break;
            case 7: ax_vtc <<0,0,1; break;
            case 8: ax_vtc <<0,0,1; break;
            case 9: ax_vtc <<0,0,1; break;
            case 10: ax_vtc <<0,0,1; break;
            case 11: ax_vtc <<0,0,1; break;
            default: break;
        }

        Eigen::Vector3d AX_vtc = cur_lnk_tf.linear()*ax_vtc;
        TP_task_map_["endeff_target"].TskJacobian.block(0,i,3,1) = AX_vtc.cross((ee_tf.translation()-cur_lnk_tf.translation()));
        TP_task_map_["endeff_target"].TskJacobian.block(3,i,3,1) = AX_vtc;
    }

    Eigen::VectorXd temp(Eigen::Map<Eigen::VectorXd>(TP_task_map_["endeff_target"].TskJacobian.data(), 
                                              TP_task_map_["endeff_target"].TskJacobian.cols()*TP_task_map_["endeff_target"].TskJacobian.rows()));
    ee_jacobian.push_back(temp);

    //TP_task_map_["endeff_target"].TskJacobian.block(0,6,6,6) = ur10Proj * urJac;
    //std::cout << "EE JACOBIAN:\n"<< std::setprecision(2) << TP_task_map_["endeff_target"].TskJacobian << std::endl;
    //std::cout << "JAC NORM:\n" << std::setprecision(2) << jacNorm << std::endl;

    //std::cout << "JACOBIAN MAT:\n" << std::setprecision(2) << Jacobian << std::endl;
    //std::cout << "JACOBIAN ANA:\n" << std::setprecision(2) << TP_task_map_["endeff_target"].TskJacobian << std::endl;
}

void JointRobotTP::Update_TskJac_ObstAvoidance(){
    std::string last_frame_name = Prx_task_pts_OBAV_[0].link_id; // save the name of the frame to compute the jacobian to
    std::string ee_frame_name;
    for(int i=0; i<NDOF; ++i){
        if(frame_names_[i] == last_frame_name){
            if(i == NDOF-1){
                ee_frame_name = TOOL;
            }else{
                ee_frame_name = frame_names_[i+1];
            }
        }
    }
    int RefRate_sz = TP_task_map_["obstacle_avoidance"].RefRate.size();
    // compute the Jacobian up to the ee_frame, than attach the RIGID BODY Jacobian

    Eigen::Affine3d ee_frame_tf = getGenericTransformation(KUKA_BASE_LINK, ee_frame_name);
    Eigen::MatrixXd Jac = Eigen::MatrixXd::Zero(6,NDOF);
    TP_task_map_["obstacle_avoidance"].TskJacobian.resize(RefRate_sz,NDOF);
    // var definition
    Eigen::Affine3d cur_lnk_tf;
    Eigen::Vector3d ax_vtc;
    bool last_link = false;
    for(int i=0; i<NDOF; ++i){
        if(frame_names_[i] == ee_frame_name){
            last_link = true;
        }
        cur_lnk_tf = getGenericTransformation(KUKA_BASE_LINK, frame_names_[i]);
        switch(i){
            case 0:  ax_vtc << 0, 0,-1;  break;
            case 1:  ax_vtc << 0, 1, 0;  break;
            case 2:  ax_vtc << 0, 1, 0;  break;
            case 3:  ax_vtc <<-1, 0, 0;  break;
            case 4:  ax_vtc << 0, 1, 0;  break;
            case 5:  ax_vtc <<-1, 0, 0;  break;
            case 6:  ax_vtc << 0, 0, 1;  break;
            case 7:  ax_vtc << 0, 0, 1;  break;
            case 8:  ax_vtc << 0, 0, 1;  break;
            case 9:  ax_vtc << 0, 0, 1;  break;
            case 10: ax_vtc << 0, 0, 1;  break;
            case 11: ax_vtc << 0, 0, 1;  break;
            default: break;
        }

        Eigen::Vector3d AX_vtc = cur_lnk_tf.linear()*ax_vtc; // rot matrix * joint axes
        Jac.block(0,i,3,1) = AX_vtc.cross((ee_frame_tf.translation() - cur_lnk_tf.translation()));
        Jac.block(3,i,3,1) = AX_vtc;
        if(last_link){
            break;
        }
    }
    // rigid body jacobian
    Eigen::MatrixXd skew_mat = Eigen::MatrixXd::Zero(3,3);
    Eigen::Vector3d JtS = Eigen::Vector3d(Prx_task_pts_OBAV_[0].min_point_robot.x, Prx_task_pts_OBAV_[0].min_point_robot.y, Prx_task_pts_OBAV_[0].min_point_robot.z);
    Eigen::VectorXd r = JtS - ee_frame_tf.translation(); 
    //Eigen::VectorXd r = JtS - cur_lnk_tf.translation(); 
    skew_mat << 0,-r(2),r(1),r(2),0,-r(0),-r(1),r(0),0;
    Eigen::MatrixXd rgdJac = Eigen::MatrixXd::Identity(6,6);
    rgdJac.block(0,3,3,3) = skew_mat.transpose();

    Eigen::MatrixXd temp = rgdJac * Jac;
    TP_task_map_["obstacle_avoidance"].TskJacobian = temp.block(0,0,RefRate_sz,NDOF);
}

void JointRobotTP::Update_TskJac_ObstAvoidance_setBased(){
    std::string task_name = "obstacle_avoidance_setbased";
    int RefR_sz = TP_task_map_[task_name].RefRate.size();
    TP_task_map_[task_name].TskJacobian = Eigen::MatrixXd::Zero(RefR_sz, RefR_sz);

    int equal_to_obav=0;
    // temp var definition
    Eigen::Vector3d dvec, ax_vtc, AX_vtc, RobMinPoint;
    Eigen::VectorXd r;
    Eigen::Affine3d ee_frame_tf, cur_lnk_tf;
    Eigen::MatrixXd skew_mat, Jac, rgdJac;

    for(int i=0; i<RefR_sz; ++i){
        // looping for all the frames, save distance vector --> already normalized;
        for(int j=0; j<Prx_task_pts_OBAV_.size(); j++){     
            if(frame_names_[i] == Prx_task_pts_OBAV_[j].link_id){
                dvec = Eigen::Vector3d(Prx_task_pts_OBAV_[j].min_point_vector.x, 
                                       Prx_task_pts_OBAV_[j].min_point_vector.y, 
                                       Prx_task_pts_OBAV_[j].min_point_vector.z);

                RobMinPoint = Eigen::Vector3d(Prx_task_pts_OBAV_[j].min_point_robot.x, 
                                              Prx_task_pts_OBAV_[j].min_point_robot.y, 
                                              Prx_task_pts_OBAV_[j].min_point_robot.z);   
            }
        }
        
        // set end effector transform (with control for last link)
        if(i+1 == NDOF){
            ee_frame_tf = getGenericTransformation(KUKA_BASE_LINK, frame_names_[i]);
        }else{
            ee_frame_tf = getGenericTransformation(KUKA_BASE_LINK, frame_names_[i+1]);
        }
        
        Jac = Eigen::MatrixXd::Zero(6, NDOF);
        rgdJac = Eigen::MatrixXd::Zero(6,6);

        for(int k=0; k<NDOF; ++k){
            cur_lnk_tf = getGenericTransformation(KUKA_BASE_LINK, frame_names_[k]);
            switch(k){
                case 0:  ax_vtc << 0, 0,-1;  break;
                case 1:  ax_vtc << 0, 1, 0;  break;
                case 2:  ax_vtc << 0, 1, 0;  break;
                case 3:  ax_vtc <<-1, 0, 0;  break;
                case 4:  ax_vtc << 0, 1, 0;  break;
                case 5:  ax_vtc <<-1, 0, 0;  break;
                case 6:  ax_vtc << 0, 0, 1;  break;
                case 7:  ax_vtc << 0, 0, 1;  break;
                case 8:  ax_vtc << 0, 0, 1;  break;
                case 9:  ax_vtc << 0, 0, 1;  break;
                case 10: ax_vtc << 0, 0, 1;  break;
                case 11: ax_vtc << 0, 0, 1;  break;
                default: break;
            }

            AX_vtc = cur_lnk_tf.linear()*ax_vtc; // rot matrix * joint axes
            Jac.block(0,k,3,1) = AX_vtc.cross((ee_frame_tf.translation() - cur_lnk_tf.translation()));
            Jac.block(3,k,3,1) = AX_vtc;
        }
        
        // rigid body jacobian
        skew_mat = Eigen::MatrixXd::Zero(3,3);
        r = RobMinPoint - ee_frame_tf.translation(); 
        skew_mat << 0,-r(2),r(1),r(2),0,-r(0),-r(1),r(0),0;
        rgdJac.block(0,3,3,3) = skew_mat.transpose();
        
        // compose the TASK JACOBIAN LINE
        TP_task_map_[task_name].TskJacobian.block(i,0,1,NDOF) = - dvec.transpose() * (rgdJac * Jac).block(0,0,3,NDOF);
    }
}

void JointRobotTP::Update_TskJac_MinAlt(){
    int Jac_cols = TP_task_map_["endeff_target"].TskJacobian.cols();
    int Jac_rows = TP_task_map_["endeff_target"].TskJacobian.rows();

    Eigen::MatrixXd Jac = TP_task_map_["endeff_target"].TskJacobian; // take only the linear part of the endeffector jacobian

    TP_task_map_["min_altitude"].TskJacobian.resize(Jac_rows, Jac_cols);
    TP_task_map_["min_altitude"].TskJacobian = Jac;
    //std::cout << "MAJ: " << TP_task_map_["min_altitude"].TskJacobian.format(Eigen::IOFormat(3, 0, ", ", "; ", "", "", "", "")) << std::endl;
}
// --------------------------------------------------------------------- TASK JACOBIAN