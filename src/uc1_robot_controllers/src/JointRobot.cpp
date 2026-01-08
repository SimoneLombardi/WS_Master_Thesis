#include "JointRobot.hpp"
#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"

#include "RobotInterface.hpp"

#include <fstream>
#include <iostream>


using namespace std::chrono_literals;

void JointRobot::initialize(rclcpp::Node::SharedPtr node_joint_robot, rclcpp::Node::SharedPtr node_kuka, rclcpp::Node::SharedPtr node_ur10)
{
    // Initialize the Kuka and UR10e robots
    kuka_robot_->initialize(node_kuka);
    ur10_robot_->initialize(node_ur10);

    std::cout << " \n\n---- initialization sequence for JointRobot structure ----" << std::endl;

    node_ = node_joint_robot; // Set the node for JointRobot
    debug_trace_publisher_ = node_->create_publisher<std_msgs::msg::String>("debug_trace", 10);

    // Initialize JointRobot parameters
    setJoint_nameVector();
    std::cout << "[init JR] Joint names vector OK: " << std::endl;
    std::cout << joint_names_.size() << " " << joint_names_tf_chain.size() << std::endl;

    setJoint_qVector(); // set the joint positions vector
    std::cout << "[init JR] joint variable vector OK: " << std::endl;
    std::cout << joint_q_.size() << std::endl;

    setJoint_jacobian(); // set the joint jacobian
    std::cout << "[init JR] jacobian" << std::endl;
    std::cout << "Comp: " << joint_jacobian_complete_.rows() << "x" << joint_jacobian_complete_.cols() << "Slid: " << joint_jacobian_slidingUR10_.rows() << "x" << joint_jacobian_slidingUR10_.cols() << std::endl;

    setJoint_transformChain(); // set the joint transformations
    std::cout << "[init JR] tf chain" << std::endl;
    std::cout << joint_transforms_.size() << std::endl;

    std::cout << "\n\n ACTION server init" << std::endl;

    // subscriber
    proximity_task_subscriber_ = node_->create_subscription<uc1_robot_perception::msg::ProximityTaskArray>(
        "/proximity_task_control",
        rclcpp::QoS(10),
        std::bind(&JointRobot::proximityTaskCallback, this, std::placeholders::_1)
    );

    // action server initialization
    move_robot_action_server_ = rclcpp_action::create_server<uc1_robot_controllers_interfaces::action::MoveRobot>(
        node_->get_node_base_interface(),
        node_->get_node_clock_interface(),
        node_->get_node_logging_interface(),
        node_->get_node_waitables_interface(),
        "move_robot",

        [this](const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const uc1_robot_controllers_interfaces::action::MoveRobot::Goal> goal) {
            return this->handle_goal(uuid, goal);
        },

        [this](const std::shared_ptr<rclcpp_action::ServerGoalHandle<uc1_robot_controllers_interfaces::action::MoveRobot>> goal_handle){
            return this->handle_cancel(goal_handle);
        },

        [this](const std::shared_ptr<rclcpp_action::ServerGoalHandle<uc1_robot_controllers_interfaces::action::MoveRobot>> goal_handle) {
            this->handle_accepted(goal_handle);
        },
        rcl_action_server_get_default_options()
    );

    goal_frame_broadcaster_ = std::make_shared<TfGoalBroadcaster>(node_);
    // action server initialization

    std::cout << "ACTION server init complete" << std::endl;
    std::this_thread::sleep_for(500ms);

    RCLCPP_INFO(node_kuka->get_logger(), "JointRobot initialized with Kuka robot.");
    RCLCPP_INFO(node_ur10->get_logger(), "JointRobot initialized with UR10e robot.");
}

// ----------------------------------------------------------------------------------------------------------SETTER METHODS
void JointRobot::setJoint_nameVector(){
    // create temporary vectors 
    std::vector<std::string> kuka_names = kuka_robot_->getFrameList();
    std::vector<std::string> ur10_names = ur10_robot_->getFrameList();

    joint_names_.resize(kuka_names.size() + ur10_names.size());
    std::copy(kuka_names.begin(), kuka_names.end(), joint_names_.begin());
    std::copy(ur10_names.begin(), ur10_names.end(), joint_names_.begin() + kuka_names.size());

    // names vector, no redundancy --> remove kuka_base_frame and ur10_base_frame
    // remove first element of each vector
    kuka_names.erase(kuka_names.begin()); // remove the first element
    ur10_names.erase(ur10_names.begin()); // remove the first element

    // same as other case
    joint_names_tf_chain.resize(kuka_names.size() + ur10_names.size());
    std::copy(kuka_names.begin(), kuka_names.end(), joint_names_tf_chain.begin());
    std::copy(ur10_names.begin(), ur10_names.end(), joint_names_tf_chain.begin() + kuka_names.size());
    
    //shrink to fit
    joint_names_.shrink_to_fit();
    joint_names_tf_chain.shrink_to_fit();
}

void JointRobot::setJoint_qVector(){
    // create temporary vectors
    Eigen::VectorXd kuka_q = kuka_robot_->getJointPositions();
    Eigen::VectorXd ur10_q = ur10_robot_->getJointPositions();
    // instantiate after for initializing the dimenision
    joint_q_.resize(kuka_q.size()+ur10_q.size());

    std::copy(kuka_q.begin(), kuka_q.end(), joint_q_.begin());
    std::copy(ur10_q.begin(), ur10_q.end(), joint_q_.begin() + kuka_q.size());
} 

void JointRobot::setJoint_jacobian(){
    setJoint_jacobian_complete();
    setJoint_jacobian_slidingUR10();
}

void JointRobot::setJoint_jacobian_complete(){
    Eigen::MatrixXd J_kuka = kuka_robot_->computeJacobian("kuka_link_6");
    Eigen::MatrixXd J_ur10 = ur10_robot_->computeJacobian("tool0");

    Eigen::MatrixXd ur10_projector = (kuka_robot_->getGenericTransformation("kuka_base_link", "base_link")).linear();
    Eigen::VectorXd ur10_tot_trasl = (kuka_robot_->getGenericTransformation("base_link", "tool0")).translation();
    //std::cout << std::fixed << std::setprecision(1) << "ur10 tot traslation:\n" << ur10_tot_trasl << std::endl;

    Eigen::MatrixXd J_jointR(6,12);
    // insert kuka and ur10 ANGULAR PART
    J_jointR.block(3,0,3,6) = J_kuka.block(3,0,3,6);
    J_jointR.block(3,6,3,6) = ur10_projector * J_ur10.block(3,0,3,6);


    //std::cout << "control 1\n" << std::endl;
    // insert kuka and ur10 LINEAR PART
    Eigen::MatrixXd temp(3,6);
    temp.leftCols(3) = Eigen::Matrix3d::Identity(3,3); 
    temp.rightCols(3) = -skew(ur10_projector*ur10_tot_trasl);
    //std::cout << "control 2\n" << std::endl;
    //std::cout << "temp:\n" << temp << std::endl;
    J_jointR.block(0,0,3,6) = temp * J_kuka;
    //std::cout << "control 3\n" << std::endl;
    J_jointR.block(0,6,3,6) = ur10_projector * J_ur10.block(0,0,3,6);

    joint_jacobian_complete_.resize(6,12);
    joint_jacobian_complete_ = J_jointR;
}

void JointRobot::setJoint_jacobian_slidingUR10(){
    // get ur10 jacobian
    Eigen::MatrixXd ur10_J = ur10_robot_->computeJacobian(ur10_tool_frame_);

    // TRASFORMAZIONE DAL URBASE AL KUKABASE, esprimere un punto in ur1obase in kukabase
    kuka_base_transform_ = kuka_robot_->getGenericTransformation(kuka_base_frame_, ur10_base_frame_);
    Eigen::MatrixXd kuka_base_rot = kuka_base_transform_.linear();

    // project ur10 jacobian to kuka base frame
    // jacobian is 6x6 but the projector is 3x3 so i have to compose the matrix with 2 block diagonals
    Eigen::MatrixXd jac_projector = Eigen::MatrixXd::Zero(6, 6);
    jac_projector.block(0, 0, 3, 3) = kuka_base_rot;
    jac_projector.block(3, 3, 3, 3) = kuka_base_rot;

    Eigen::MatrixXd sliding_jacobian(6, 3);
    sliding_jacobian.topLeftCorner(3, 3) = Eigen::MatrixXd::Identity(3, 3); // first 3 rows are identity for sliding dof
    sliding_jacobian.bottomRightCorner(3, 3) = Eigen::MatrixXd::Zero(3, 3); // last 3 rows are zero for sliding dof

    joint_jacobian_slidingUR10_.resize(6, 9); // [6x3 sliding dof][6x6 ur10 dof]

    // concatenate jacobians
    joint_jacobian_slidingUR10_.block(0, 0, 6, 3) = sliding_jacobian;                 // first 6 columns-> kuka jacobian
    joint_jacobian_slidingUR10_.block(0, 3, 6, 6) = jac_projector * ur10_J;           // last 6 columns -> ur10 jacobian projected to kuka base frame  
}

void JointRobot::setJoint_transformChain(){
    for(short indx=0; indx < (joint_names_.size()); ++indx)
    {
        joint_transforms_.push_back(kuka_robot_->getGenericTransformation(kuka_base_frame_,joint_names_[indx]));
    }
}

void JointRobot::setJoint_initConfig(){
    switch(robot_initialization_state_)
    {
        case RobotInitializationState::SINGULARITY_SINGULARITY:
            kuka_q_init_ << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
            ur10_q_init_ << 0.0, -1.59, 0.0, -1.59, 0.0, 0.0;
            break;
        case RobotInitializationState::SINGULARITY_MOBILITY:
            kuka_q_init_ << 0.0, 0.0, 0.0, 0.0, 0.0, 0.0;
            ur10_q_init_ << -3.14159, -2.10757, -1.83066, -0.774163, -1.5708, -0.0300288;
            break;
        case RobotInitializationState::MOBILITY_SINGULARITY:
            kuka_q_init_ << 0.0, 0.785398, -1.578, 0.0, 0.785398, 0.0;
            ur10_q_init_ << 0.0, -1.59, 0.0, -1.59, 0.0, 0.0;
            break;
        case RobotInitializationState::MOBILITY_MOBILITY:
            kuka_q_init_ << 0.0, 0.785398, -1.578, 0.0, 0.785398, 0.0;
            ur10_q_init_ << -3.14159, -2.10757, -1.83066, -0.774163, -1.5708, -0.0300288;
            break;
        default:
            RCLCPP_ERROR(node_->get_logger(), "Invalid robot initialization state.");
    }
}
// ---------------------------------------------------------------------------------------------------------- UPDATER METHODS

void  JointRobot::update_robotInitConfigState(const RobotInitializationState& init_state){
    robot_initialization_state_ = init_state; // update the robot initialization state
}
// ---------------------------------------------------------------------------------------------------------- UPDATER METHODS

// ---------------------------------------------------------------------------------------------------------- GETTER METHODS
std::vector<std::string> JointRobot::getJoint_nameVector(int select){
    if(select == 0){
        return joint_names_; // get all the names
    }else{
        return joint_names_tf_chain; // get the names for the jacobian (without base frames)
    }
}

Eigen::VectorXd  JointRobot::getJoint_qVector(){
    return joint_q_; // return the joint positions vector
}

Eigen::MatrixXd JointRobot::getJoint_jacobian(){
    if(jacobian_dim_param == 0){
        return joint_jacobian_complete_; 
    }else if(jacobian_dim_param == 1){
        return joint_jacobian_slidingUR10_;
    }else{
        RCLCPP_ERROR(node_->get_logger(), "Invalid jacobian dimension parameter.");
        return Eigen::MatrixXd::Zero(6,12);
    }
}

Eigen::MatrixXd JointRobot::getJoint_jacobian_complete(){
    return joint_jacobian_complete_; // return the joint jacobian with sliding UR10e
}

Eigen::MatrixXd JointRobot::getJoint_jacobian_slidingUR10(){
    return joint_jacobian_slidingUR10_; // return the joint jacobian with sliding UR10e
}

std::vector<Eigen::Affine3d> JointRobot::getJoint_transformChain(){
    return joint_transforms_; // return the joint transformations
}

Eigen::Affine3d JointRobot::getGenericTransformation(const std::string& target_frame, const std::string& source_frame){
    // get the transformation between two frames
    return kuka_robot_->getGenericTransformation(target_frame, source_frame);
}

RobotInitializationState JointRobot::getRobotInitializationState() const {
    return robot_initialization_state_;
}

std::vector<Eigen::VectorXd> JointRobot::getJoint_initStateVector(){
    std::vector<Eigen::VectorXd> init_states;
    init_states.push_back(kuka_q_init_);
    init_states.push_back(ur10_q_init_);
    return init_states;
} 

// ----------------------------------------------------------------------------------------------------------CONTROLLER METHODS
void JointRobot::reachJointPosition_single(int robot_code, Eigen::VectorXd q_err, Eigen::VectorXd q_des){
    if (robot_code == 0){ // Kuka robot{
        // run joint control loop for Kuka robot
        kuka_robot_->runJointControlLoop(q_err, q_des);
    }else if (robot_code == 1){ // UR10e robot
        // run joint control loop for UR10e robot
        ur10_robot_->runJointControlLoop(q_err, q_des);
    }else{
        //std::cout << "[JointRobot] Invalid robot code: " << robot_code << ". Use 0 for Kuka and 1 for UR10e." << std::endl;
    }
}

void JointRobot::reachJointPosition(Eigen::VectorXd q_err, Eigen::VectorXd q_des){ // Run joint control loop for both robots
    if((q_err.size() == q_des.size()) && (q_err.size() == 12)){
        //std::cout << "[JointRobot] running joint control loop" << std::endl;
        Eigen::VectorXd err(6), des(6);

        // run joint control loop for Kuka robot
        err = q_err.head(6);
        des = q_des.head(6);
        kuka_robot_->runJointControlLoop(err, des);

        // run joint control loop for UR10e robot
        err = q_err.tail(6);
        des = q_des.tail(6);
        //std::cout << "[JointRobot] running joint control loop ur10" << std::endl;
        ur10_robot_->runJointControlLoop(err, des);
        
    }else{
        std::cout << "[JointRobot_reachJointPosition] Error: q_err and q_des are the wrong size." << q_des.size() << " " << q_err.size() << std::endl;
    }
}

void JointRobot::sendBaseVelocityCommand(Eigen::VectorXd vel){
    if(vel.size() == 3){
        //Eigen::Affine3d fxd_tf = getGenericTransformation(kuka_tool_frame_, ur10_base_frame_);
        Eigen::VectorXd fullVel_vect(6);

        // project velocity in kuka_link_6 frame
        //Eigen::VectorXd transformed_vel = trasformVector("base_link", "kuka_link_6", vel);

        // create the full velocity vector, only linear velocity
        fullVel_vect.head(3) = vel;
        fullVel_vect.tail(3) = Eigen::Vector3d::Zero(); 

        // use the cartesian velocity as desired velocity for the tool of the kuka
        Eigen::MatrixXd J = kuka_robot_->computeJacobian(kuka_tool_frame_);
        Eigen::MatrixXd Jpinv = kuka_robot_->computePseudoInverse(J);

        Eigen::VectorXd qdot_des = 0.03 * (Jpinv * fullVel_vect);

        kuka_robot_->updateJointPositionCommand(joint_q_.head(6), qdot_des);
    }else if (vel.size() == 6){
        // send directly the velocity to the kuka robot
        kuka_robot_->updateJointPositionCommand(joint_q_.head(6), vel);
    }
}

void JointRobot::runCartesianReachingLoop(std::string goal_frame, bool reached_goal){ // Run Cartesian reaching loop for both robots
    rclcpp::Rate loop_rate(100);

    TPComputation tp_controller;

    int temp = 0;
    while (rclcpp::ok() && reached_goal==false)
    {   
        // ------------------------------ state update
        setJoint_qVector(); 
        setJoint_transformChain();  // prima del jacobian per aggiornare le tf
        setJoint_jacobian();
        // ------------------------------ state update

        // temporaneo ----------------------------------------------- joint limit act function
        Eigen::MatrixXd jl_ActTask = Eigen::MatrixXd::Zero(12, 12); // --> t ref=joint_q_ (12x1) --> activation fnc stessa dim
        float jl_up = 2.8; 
        float jl_low = -2.8;
        for (int i =7; i<12; i++){
            jl_ActTask(i,i) = (ur10_robot_->IncreasingBellShapedFunction(jl_up-0.1,jl_up,0.0,1.0, joint_q_[i]))+(ur10_robot_->DecreasingBellShapedFunction(jl_low-0.1,jl_low,0.0,1.0, joint_q_[i]));
        }
        std::cout << "JL ACT TASK:\n" << std::setprecision(2) << jl_ActTask << std::endl;
        // temporaneo ----------------------------------------------- joint limit act function

        // positiona and orientation error computation
        Eigen::Affine3d goal_tf = kuka_robot_->getGenericTransformation(kuka_base_frame_, goal_frame); 
        cart_err_ = kuka_robot_->computeCartesianReachingTask(goal_tf, joint_transforms_.back()); 

        std::cout << "[JR old]: " << cart_err_ << std::endl;

        // TASK STOP CONDITION
        // update the norm buffer
        float curr_norm = cart_err_.norm();
        carterr_norm_buff_[0] = carterr_norm_buff_[1];
        carterr_norm_buff_[1] = curr_norm;

        // compute the rate of change 
        rate_of_change = (carterr_norm_buff_[1] - carterr_norm_buff_[0]) / (loop_rate.period().count()/1e9);
        if (rate_of_change_counter < 0.05) {
            if(rate_of_change_counter > temp){
                temp = rate_of_change_counter;
            }
            rate_of_change_counter = rate_of_change_counter + 1;
        } else {
            rate_of_change_counter = 0;
        }

        //std_msgs::msg::String msg;
        //msg.data = "RoC: " + std::to_string(rate_of_change) + " | NM: " + std::to_string(carterr_norm_buff_[0]) + " " + std::to_string(carterr_norm_buff_[1]) + " | C: " + std::to_string(rate_of_change_counter) + " " + std::to_string(temp);
        //debug_trace_publisher_->publish(msg);

        if (carterr_norm_buff_[1] < 0.02) {
            std::cout << "STOP CONDITION REACHED" << std::endl;
            reached_goal = true;
        }
        
        /*  NORMAL WAY
        // compute desired velocity 
        const std::vector<float> partition = {0.1, 0.1}; // partition for pseudo-inverse
        Eigen::MatrixXd J = getJoint_jacobian();
        Eigen::MatrixXd Jpinv = computePseudoInverse(J, partition);

        //std::cout << "[JACOBIAN SIZE CONTROL] Jacobian: " << J.rows() << "x" << J.cols() << " Jpinv: " << Jpinv.rows() << "x" << Jpinv.cols() << std::endl;

        Eigen::VectorXd qdot_des_temp = (Jpinv * cart_err_);
        */

        // TP ALGO
         //  0.0001,   0.01, 10
        tp_controller.init_TPComputation(12, 0.1, 0.01, 10.0); 

        //tp_controller.computeTP_step(Eigen::MatrixXd::Identity(6,6), getJoint_jacobian(), cart_err_); // joint limit task
        tp_controller.computeTP_step("joint_limits", jl_ActTask, Eigen::MatrixXd::Identity(12,12), joint_q_);         // joint limit task
        tp_controller.computeTP_step("target", Eigen::MatrixXd::Identity(6,6), getJoint_jacobian(), cart_err_); // tool target task
        Eigen::VectorXd qdot_des_temp = tp_controller.getTP_ydot();

        tp_controller.kill_TPComputation(); // clear internal data to ensure no data carry over to next iteration
        // TP ALGO

        float Kp_kuka = 0.05;
        float Kp_ur10 = 0.5;

        Eigen::VectorXd qdot_des = Eigen::VectorXd::Zero(12);
        qdot_des.head(6) = Kp_kuka*qdot_des_temp.head(6);
        qdot_des.tail(6) = Kp_ur10*qdot_des_temp.tail(6);

        //  ---------------------------------------- send velocity commands 
        // discrimination on vector size
        int ur10_dof = 6;
        int kuka_dof;
        if(jacobian_dim_param == 0){
            kuka_dof = 6;
        }else if(jacobian_dim_param == 1){
            kuka_dof = 3;
        }

        //ur10_robot_->sendJointVelocityCommand(qdot_des.tail(ur10_dof)); 
        //sendBaseVelocityCommand(qdot_des.head(kuka_dof)); 

        // -------------------------------------------------------------------------------------- SAVE JOINTQ VECTOR AND QDOT_DES ON FILE
        std::ofstream file_1("/home/simone/Documents/jointq_log.txt", std::ios::app);
        if(file_1.is_open()){
            for(int i=0; i<joint_q_.size(); i++){
                file_1 << std::fixed << std::setprecision(4) << joint_q_[i] << " ";
            }
            file_1 << "\n";
            file_1.close();
        }

        std::ofstream file_2("/home/simone/Documents/qdot_des_log.txt", std::ios::app);
        if(file_2.is_open()){
            for(int i=0; i<qdot_des.size(); i++){
                file_2 << std::fixed << std::setprecision(4) << qdot_des[i] << " ";
            }
            file_2 << "\n";
            file_2.close();
        }

        std::ofstream file_3("/home/simone/Documents/sing_val_log.txt", std::ios::app);
        if(file_3.is_open()){
            for(int i=0; i<singular_values_.size(); i++){
                file_3 << std::fixed << std::setprecision(6) << singular_values_[i] << " ";
            }
            file_3 << "\n";
            file_3.close();
        }
        // ---------------------------------------------------------------------------------------- SAVE JOINTQ VECTOR AND QDOT_DES ON FILE

        loop_rate.sleep();
    }
}


// ----------------------------------------------------------------------------------------------------------SUB CALLBACKS
void JointRobot::proximityTaskCallback(const uc1_robot_perception::msg::ProximityTaskArray::SharedPtr msg){
    for(const auto& task : msg->proximity_tasks){
        if(task.link_id == kuka_base_frame_ || task.link_id == ur10_base_frame_){
            continue;
        }else{
            proximity_task_points_[task.link_id] = std::make_pair(task.distance, Eigen::Vector3d(task.min_point_robot.x, task.min_point_robot.y, task.min_point_robot.z));
        }
    }

    std_msgs::msg::String debg_msg;

    Eigen::IOFormat fmt(3, 0, ", ", "; ", "", "", "", "");
    for (const auto& [link_id, data] : proximity_task_points_)
    {
        std::ostringstream oss;
        oss << data.second.transpose().format(fmt);

        debg_msg.data += link_id + ": " +
                         std::to_string(data.first) + " | " +
                         oss.str() + "\n";
    }

    debug_trace_publisher_->publish(debg_msg);
}


// ----------------------------------------------------------------------------------------------------------VARIE METHODS
Eigen::VectorXd JointRobot::trasformVector(const std::string& source_frame, const std::string& target_frame, Eigen::VectorXd v){
    // Get the transformation between the source frame and the target frame
    Eigen::Affine3d tf = kuka_robot_->getGenericTransformation(target_frame, source_frame);
    
    // Transform the vector using the transformation matrix
    Eigen::VectorXd transformed_vector = tf.linear() * v.head(3) + tf.translation();
    
    return transformed_vector; // Return the transformed vector
}

Eigen::MatrixXd JointRobot::computePseudoInverse(const Eigen::MatrixXd& jacobian, const std::vector<float> partition){
    double mu = 0.1;

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(jacobian, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::MatrixXd SigmaPlus(jacobian.cols(), jacobian.rows());
    Eigen::VectorXd eigen = svd.singularValues();

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

    std_msgs::msg::String msg;
    msg.data = "test msg";
    //debug_trace_publisher_->publish(msg);
    
    /*
    std::cout << " " << SigmaPlus.rows() << "x" << SigmaPlus.cols();
    std::cout << "V size: " << V.rows() << "x" << V.cols() << "\n";
    std::cout << "UT size: " << UT.rows() << "x" << UT.cols() << "\n";
    */
    singular_values_.resize(SigmaPlus.diagonal().size());
    singular_values_ = SigmaPlus.diagonal();

    return V * SigmaPlus * UT;
}

Eigen::MatrixXd JointRobot::skew(const Eigen::VectorXd& v){
    Eigen::MatrixXd skew_mat(3, 3);
    skew_mat <<     0, -v(2),  v(1),
                 v(2),     0, -v(0),
                -v(1),  v(0),     0;
    return skew_mat;
}

Eigen::VectorXd JointRobot::check_work_limits(const Eigen::VectorXd& v){
    Eigen::VectorXd out = Eigen::VectorXd::Zero(3);
    if(v.size() == 3){
        out[0] = std::min(std::max(v[0], -x_lim), x_lim);
        out[1] = std::min(std::max(v[1], -y_lim), y_lim);
        out[2] = std::min(std::max(v[2], 0.0), z_lim);
        return out;
    }else{
        RCLCPP_INFO(node_->get_logger(), "goal traslation vector, wrong size");
        return out;
    }
}

// ----------------------------------------------------------------------------------------------------------VARIE METHODS



// ---------------------------------------------------------------------------------------------------------- ACTION SERVER CALLBACKS
rclcpp_action::GoalResponse JointRobot::handle_goal(const rclcpp_action::GoalUUID & uuid, std::shared_ptr<const uc1_robot_controllers_interfaces::action::MoveRobot::Goal> goal){
    (void)uuid;
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE; 
}

rclcpp_action::CancelResponse JointRobot::handle_cancel(const std::shared_ptr<rclcpp_action::ServerGoalHandle<uc1_robot_controllers_interfaces::action::MoveRobot>> goal_handle){
    (void)goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
}

void JointRobot::handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<uc1_robot_controllers_interfaces::action::MoveRobot>> goal_handle){
    using namespace std::placeholders;

    std::thread{std::bind(&JointRobot::execute, this, _1), goal_handle}.detach();
}

void JointRobot::execute(const std::shared_ptr<rclcpp_action::ServerGoalHandle<uc1_robot_controllers_interfaces::action::MoveRobot>> goal_handle){
    const auto goal = goal_handle->get_goal();
    auto feedback = std::make_shared<uc1_robot_controllers_interfaces::action::MoveRobot::Feedback>();
    auto result = std::make_shared<uc1_robot_controllers_interfaces::action::MoveRobot::Result>();

    init_config_param = goal->init_config_code;
    jacobian_dim_param = goal->jacobian_type_code;

    // checke goal cancellation
    if(goal_handle->is_canceling()){
        result->result = "bad stuff"; // VEDERE DEFINIZIONE DELL ACTION
        goal_handle->canceled(result);
        
        return;
    }

    //std::cout << "[execute] 1" << std::endl;
    // --------------------------------------------------------------------- init position reaching
    if(init_config_param == 0){

        update_robotInitConfigState(RobotInitializationState::SINGULARITY_SINGULARITY);
        std::cout << "\nRS: SINGULARITY_SINGULARITY" << std::endl;

    }else if(init_config_param == 1){

        update_robotInitConfigState(RobotInitializationState::SINGULARITY_MOBILITY);
        std::cout << "\nRS: SINGULARITY_MOBILITY" << std::endl;

    }else if(init_config_param == 2){

        update_robotInitConfigState(RobotInitializationState::MOBILITY_SINGULARITY);
        std::cout << "\nRS: MOBILITY_SINGULARITY" << std::endl;

    }else if(init_config_param == 3){

        update_robotInitConfigState(RobotInitializationState::MOBILITY_MOBILITY);
        std::cout << "\nRS: MOBILITY_MOBILITY" << std::endl;
    
    }else if(init_config_param == -1){
        // stay in current position
        std::cout << "\nRS: STAND" << std::endl;

    }else{
        RCLCPP_ERROR(node_->get_logger(), "Invalid robot initialization state.");
        result->result = "bad stuff";
        goal_handle->canceled(result);
        return;
    }

    if(init_config_param != -1){
        setJoint_initConfig();
    
        std::vector<Eigen::VectorXd> init_states = getJoint_initStateVector();
        reachJointPosition_single(KUKA_ROBOT, init_states[0], init_states[0]); 
        reachJointPosition_single(UR10_ROBOT, init_states[1], init_states[1]);

        setJoint_qVector();
        //std::cout << "\n Initalization error: " << std::endl;
        //std::cout << joint_q_.head(6) - init_states[0] << " | " << joint_q_.tail(6) - init_states[1] << std::endl;
    }
    // --------------------------------------------------------------------- init position reaching
    //
    // --------------------------------------------------------------------- goal frame broadcasting
    Eigen::VectorXd req_traslation(3); // requested vector for traslation and orientation
    req_traslation << goal->goal.translation.x, goal->goal.translation.y, goal->goal.translation.z;

    Eigen::VectorXd req_rotation(3);
    req_rotation << goal->goal.orientation.roll, goal->goal.orientation.pitch, goal->goal.orientation.yaw; 


    Eigen::MatrixXd Rz, Ry, Rx;
    Eigen::Matrix3d R_goal;
    Rz = Eigen::AngleAxisd(req_rotation[2], Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Ry = Eigen::AngleAxisd(req_rotation[1], Eigen::Vector3d::UnitY()).toRotationMatrix();
    Rx = Eigen::AngleAxisd(req_rotation[0], Eigen::Vector3d::UnitX()).toRotationMatrix();
    R_goal = Rz * Ry * Rx;

    std::cout << "\nRequested goal (position): " << req_traslation.transpose() << std::endl;
    Eigen::VectorXd goal_traslation(3);
    goal_traslation = req_traslation + (getGenericTransformation(kuka_base_frame_, ur10_tool_frame_)).translation();
    std::cout << "\nRequested goal traslated (position): " << goal_traslation.transpose() << std::endl;
    Eigen::VectorXd goal_rotation(3);

    Eigen::Matrix3d fxd_prj = getGenericTransformation(kuka_tool_frame_, ur10_tool_frame_).linear();
    goal_rotation = (fxd_prj * R_goal).eulerAngles(2, 1, 0);
    
    //goal_traslation = check_work_limits(goal_traslation);

    std::string parent_frame = kuka_base_frame_; 
    std::string goal_frame  = "GOAL_FRAME";
    /*
    // save the goal and orientation
    Eigen::VectorXd traslation = Eigen::VectorXd::Zero(3);
    Eigen::Quaterniond rotation_quat(goal->goal.pose.orientation.w, goal->goal.pose.orientation.x, goal->goal.pose.orientation.y, goal->goal.pose.orientation.z);
    traslation << goal->goal.pose.position.x, goal->goal.pose.position.y, goal->goal.pose.position.z;
    rotation_quat.normalize(); 
    
    // add the distance k_base -> tool
    Eigen::VectorXd traslation_goal = Eigen::VectorXd::Zero(3); 
    Eigen::Affine3d goal_transform = getGenericTransformation(kuka_base_frame_, ur10_tool_frame_);
    traslation_goal = traslation + goal_transform.translation();

    // convert quaternion to rpy
    Eigen::VectorXd rotation = Eigen::Vector3d::Zero(3);
    rotation = rotation_quat.toRotationMatrix().eulerAngles(2, 1, 0); 

    // controlling goal frame inside operational space
    std::cout << "\ncheck goal work area limits: " << traslation_goal.transpose() << std::endl;
    traslation_goal = check_work_limits(traslation_goal);
    */
    goal_frame_broadcaster_->broadcastStaticTransform(goal_traslation, goal_rotation, parent_frame, goal_frame);
    // --------------------------------------------------------------------- goal frame broadcasting
    //
    std::cout << "Goal sent (position): " << goal_traslation.transpose() << std::endl;
    std::cout << "Goal sent (orientat): " << goal_rotation.transpose() << std::endl;
    //
    // --------------------------------------------------------------------- execute reaching loop
    std::this_thread::sleep_for(2000ms);
    bool reached_goal = false;

    std::string jac_msg = (jacobian_dim_param == 0)? "\n-- Full jacobian --" : "\n-- Slid jacobian";
    std::cout << "\n\n --- STARTING REACHING LOOP --- " << jac_msg.c_str() << std::endl;
    runCartesianReachingLoop(goal_frame, reached_goal);
    // --------------------------------------------------------------------- execute reaching loop

    if(rclcpp::ok()){
        // set the result
        result->result = "good stuff"; // VEDERE DEFINIZIONE DELL ACTION
        goal_handle->succeed(result);
    }
}
// ---------------------------------------------------------------------------------------------------------- ACTION SERVER CALLBACKS












// ----------------------------------------------------------------------------------------------------------DEBUGGER METHODS
void JointRobot::printGenericTransformation(const std::string& target_frame, const std::string& source_frame){
    // Get the transformation between the target frame and the source frame
    Eigen::Affine3d tf_kuka = kuka_robot_->getGenericTransformation(target_frame, source_frame);

    Eigen::Affine3d tf_ur10 = ur10_robot_->getGenericTransformation(target_frame, source_frame);
    // Print the transformation matrices

    std::cout << "Transformation from " << source_frame << " to " << target_frame << " for Kuka robot:\n" 
              << tf_kuka.matrix() << "\n\n";
    std::cout << "Transformation from " << source_frame << " to " << target_frame << " for UR10e robot:\n"
              << tf_ur10.matrix() << "\n\n";


    Eigen::VectorXd cart_err_kuka(6);
    Eigen::Affine3d tf2_kuka = kuka_robot_->getGenericTransformation("kuka_base_link", "tool0");
    cart_err_kuka = kuka_robot_->computeCartesianReachingTask(tf_kuka, tf2_kuka); // goal and tool frames

    Eigen::VectorXd cart_err_ur10(6);
    Eigen::Affine3d tf2_ur10 = ur10_robot_->getGenericTransformation("kuka_base_link", "tool0");
    cart_err_ur10 = ur10_robot_->computeCartesianReachingTask(tf_ur10, tf2_ur10); // goal and tool frames

    std::cout << "Cartesian error for Kuka robot: " << cart_err_kuka.transpose() << "\n";
    std::cout << "Cartesian error for UR10e robot: " << cart_err_ur10.transpose() << "\n";
}

void JointRobot::debugJointRobot(int jnm, int q, int J, int tfs, int tf_x, const std::string& target_frame, const std::string& source_frame){
    if(jnm == 1){  //print joint names
        std::vector<std::string> joint_names = getJoint_nameVector(0);
        std::cout << "Joint names for JointRobot (all):\n";
        for (const auto& name : joint_names) {
            std::cout << name << "\n";
        }

        joint_names = getJoint_nameVector(1); // get the names for the jacobian (without base frames)
        std::cout << "Joint names for JointRobot (tf chain):\n";
        for (const auto& name : joint_names) {
            std::cout << name << "\n";
        }
    }

    if(q == 1){ // print joint positions for both robots
        Eigen::VectorXd joint_q = getJoint_qVector();
        std::cout << "Joint positions for JointRobot:\n" << joint_q.transpose() << "\n";
    }

    if(J == 1){ // print joint jacobian for both robots
        setJoint_jacobian_slidingUR10();
        Eigen::MatrixXd joint_jacobian = getJoint_jacobian_slidingUR10();
        std::cout << "Joint Jacobian for JointRobot:\n" << joint_jacobian << "\n";

        //Eigen::MatrixXd pinv_jj = kuka_robot_->computePseudoInverse(joint_jacobian); // pseudo-inverse of the first 6 columns (Kuka part)
        //std::cout << "Pseudo-inverse of Joint Jacobian for JointRobot:\n" << pinv_jj << "\n";
        setJoint_jacobian_complete();
        joint_jacobian = getJoint_jacobian_complete();
        std::cout << "Joint Jacobian complete for JointRobot:\n" << joint_jacobian << "\n";
    }

    if(tfs == 1){ // print joint transformations for both robots
        setJoint_transformChain();
        std::vector<Eigen::Affine3d> joint_transforms = getJoint_transformChain();
        std::cout << "Joint transformations for JointRobot:\n";
        for (const auto& transform : joint_transforms) {
            std::cout << transform.matrix() << "\n";
        }
    }

    if(tf_x == 1){ // print generic transformation between two frames
        Eigen::Affine3d tf = kuka_robot_->getGenericTransformation(target_frame, source_frame);
        std::cout << "done with kuka method Transformation target " << target_frame << " tf source " << source_frame << ":\n" 
                  << tf.matrix() << "\n";
    }

} // Debug method to print joint robot information

void JointRobot::debugKukaRobot(int jnm, int q, int J, int tfs, int tf_x, const std::string& target_frame, const std::string& source_frame){
    if(jnm == 1){  //print joint names
        std::vector<std::string> names = kuka_robot_->getFrameList();
        std::cout << "Joint names for kuka robot:\n";
        for (const auto& name : names) {
            std::cout << name << "\n";
        }
    }

    if(q == 1){ // print joint positions for both robots
        Eigen::VectorXd q = kuka_robot_->getJointPositions();
        std::cout << "Joint positions for JointRobot:\n" << q.transpose() << "\n";
    }

    if(J == 1){ // print joint jacobian for both robots
        Eigen::MatrixXd kJ = kuka_robot_->computeJacobian("kuka_link_6");
        std::cout << "Jacobian for kukaroobt (proj on kuka base):\n" << kJ << "\n";

        Eigen::MatrixXd pinv_kJ = kuka_robot_->computePseudoInverse(kJ);
        std::cout << "Pseudo-inverse of jacobian for kuka:\n" << pinv_kJ << "\n";
    }

    if(tfs == 1){ // print joint transformations for both robots
        std::vector<Eigen::Affine3d> tf_ch = kuka_robot_->getTransformations();
        std::cout << "transformations for kuka robot:\n";
        for (const auto& transform : tf_ch) {
            std::cout << transform.matrix() << "\n";
        }
    }

    if(tf_x == 1){ // print generic transformation between two frames
        Eigen::Affine3d tf = kuka_robot_->getGenericTransformation(target_frame, source_frame);
        std::cout << "done with kuka method Transformation from " << source_frame << " to " << target_frame << ":\n" 
                  << tf.matrix() << "\n";
    }
} // Debug method to print Kuka robot information

void JointRobot::debugUR10eRobot(int jnm, int q, int J, int tfs, int tf_x, const std::string& target_frame, const std::string& source_frame){
    if(jnm == 1){  // print joint names
        std::vector<std::string> names = ur10_robot_->getFrameList();
        std::cout << "Joint names for UR10e robot:\n";
        for (const auto& name : names) {
            std::cout << name << "\n";
        }
    }

    if(q == 1){ // print joint positions for UR10e robot
        Eigen::VectorXd q = ur10_robot_->getJointPositions();
        std::cout << "Joint positions for UR10e robot:\n" << q.transpose() << "\n";
    }

    if(J == 1){ // print joint jacobian for UR10e robot
        Eigen::MatrixXd uJ = ur10_robot_->computeJacobian("tool0");
        std::cout << "Jacobian for UR10e robot (proj on ur10 base):\n" << uJ << "\n";

        Eigen::MatrixXd pinv_uJ = ur10_robot_->computePseudoInverse(uJ);
        std::cout << "Pseudo-inverse of jacobian for UR10e:\n" << pinv_uJ << "\n";
    }

    if(tfs == 1){ // print joint transformations for UR10e robot
        std::vector<Eigen::Affine3d> tf_ch = ur10_robot_->getTransformations();
        std::cout << "Transformations for UR10e robot:\n";
        for (const auto& transform : tf_ch) {
            std::cout << transform.matrix() << "\n";
        }
    }

    if(tf_x == 1){ // print generic transformation between two frames
        Eigen::Affine3d tf = ur10_robot_->getGenericTransformation(target_frame, source_frame);
        std::cout << "done with UR10e method Transformation from " << source_frame << " to " << target_frame << ":\n" 
                  << tf.matrix() << "\n";
    }
} // Debug method to print UR10e robot information



