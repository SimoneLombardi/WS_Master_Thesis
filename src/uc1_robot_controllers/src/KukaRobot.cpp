#include "KukaRobot.hpp"
#include "RobotInterface.hpp"


using namespace std::chrono_literals;


void KukaRobot::initialize(rclcpp::Node::SharedPtr node)
{
    frame_list_ = {"kuka_base_link", "kuka_link_1", "kuka_link_2", "kuka_link_3", "kuka_link_4", "kuka_link_5", "kuka_link_6"};
    node_ = node;
    // tf members
    tf_buffer_ = std::make_shared<tf2_ros::Buffer>(node_->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    // initialize tf buffers
    std::vector<Eigen::Affine3d> initial_state(frame_list_.size(), Eigen::Affine3d::Identity());
    tf_read_buffer_ = initial_state;
    tf_write_buffer_ = initial_state;

    // robot joint state
    q_ = Eigen::VectorXd::Zero(6);
    qdot_ = Eigen::VectorXd::Zero(6);
    qdot_cmd_ = Eigen::VectorXd::Zero(6);
    q_efforts_ = Eigen::VectorXd::Zero(6);
    q_target_ = Eigen::VectorXd::Zero(6);
    joint_names_.resize(6);
    ordered_joint_names_ = {"kuka_joint_a1", "kuka_joint_a2", "kuka_joint_a3", "kuka_joint_a4", "kuka_joint_a5", "kuka_joint_a6"};

    // define joint limits (for the UR10e I'll need to have them dynamic)
    q_limit_low_.resize(6);
    q_limit_up_.resize(6);
    q_limit_low_ << -0.707, -3.14, -3.14, -3.14, -3.14, -3.14; 
    q_limit_up_ << 0.707, 3.14, 3.14, 3.14, 3.14, 3.14;
    // logistic joint limits sharpness
    alpha_low_ = 20;
    alpha_up_ = 20;

    q_cmd_ = Eigen::VectorXd::Zero(6);

    // initialize IK solvers
    while (!initializeKDL())
    {
        RCLCPP_ERROR(node_->get_logger(), "Failed to initialize KDL");
    }

    // ----------------------------- pubs
    //joint_state_pub_ = node->create_publisher<sensor_msgs::msg::JointState>("/joint_states_kuka", 10);
    joint_pose_pub_ = node->create_publisher<std_msgs::msg::Float64MultiArray>("/kuka_joint_state_buffer", 10);

    // ----------------------------- timed callbacks
    // joint state (fake commands) publishing
    q_cmd_timer_ = node->create_wall_timer(
            std::chrono::milliseconds(10),
            std::bind(&KukaRobot::sendJointPositionCommand, this));

    
    // wait for the state to be published
    RCLCPP_INFO(node->get_logger(), "Starting state subscriptions...");
    std::this_thread::sleep_for(100ms);

    // ----------------------------- subs
    joint_state_sub_ = node->create_subscription<sensor_msgs::msg::JointState>(
        "/joint_states",
        rclcpp::QoS(10),
        std::bind(&KukaRobot::jointStateCallback, this, std::placeholders::_1));

    // start tf updating
    RCLCPP_INFO(node->get_logger(), "Waiting for tf...");
    std::this_thread::sleep_for(100ms);
    stop_tf_thread_ = false;
    tf_update_thread_ = std::thread(&KukaRobot::tfUpdateLoop, this);

    RCLCPP_INFO(node->get_logger(), "KUKA robot interface initialized");
}


void KukaRobot::jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
{
    // re-arranging joint names to correct sequence
    std::unordered_map<std::string, size_t> name_to_index;
    for (size_t i = 0; i < msg->name.size(); ++i)
    {
        name_to_index[msg->name[i]] = i;
    }

    // WARNING no joint velocities and efforts available for basic URDF interface
    for (size_t i = 0; i < ordered_joint_names_.size(); ++i)
    {
        const std::string &joint_name = ordered_joint_names_[i];
        if (name_to_index.find(joint_name) != name_to_index.end())
        {
            size_t index = name_to_index[joint_name];
            q_[i] = msg->position[index];
            joint_names_[i] = joint_name;
        }
    }

    //RCLCPP_INFO(rclcpp::get_logger("KukaRobot"), "KUKA JointState received");
}


// TODO Add double buffering in this
void KukaRobot::updateJointPositionCommand(Eigen::VectorXd q, Eigen::VectorXd qdot_des)
{
    for (int i = 0; i < q.size(); i++)
    {
        q_cmd_(i) = q(i) + qdot_des(i);
    }
}

void KukaRobot::sendJointPositionCommand()
{
    // build joint state message
    std_msgs::msg::Float64MultiArray joint_pos_msg;
    joint_pos_msg.data.resize(6);
    for (size_t i = 0; i < 6; ++i) {
       joint_pos_msg.data[i] = q_cmd_(i);
    }
    joint_pose_pub_->publish(joint_pos_msg);
}


void KukaRobot::tfUpdateLoop()
{
    rclcpp::Rate loop_rate(100); 

    while (!stop_tf_thread_ && rclcpp::ok())
    {
        updateTransforms(); 
        loop_rate.sleep();
    }
}

Eigen::Affine3d KukaRobot::getTransformation(const std::string& target_frame, const std::string& source_frame)
{
    try {
        geometry_msgs::msg::TransformStamped transform_stamped =
            tf_buffer_->lookupTransform(target_frame, source_frame, rclcpp::Time(0), rclcpp::Duration::from_seconds(1.0));

         // Extract position
        const auto& translation = transform_stamped.transform.translation;
        Eigen::Vector3d position(translation.x, translation.y, translation.z);

        // Extract quaternion and normalize
        const auto& rotation = transform_stamped.transform.rotation;
        Eigen::Quaterniond quaternion(rotation.w, rotation.x, rotation.y, rotation.z);
        quaternion.normalize();

        // Construct the Affine3d using position and quaternion
        Eigen::Affine3d transform = Eigen::Affine3d::Identity();
        transform.translation() = position;
        transform.linear() = quaternion.toRotationMatrix();

        return transform;

    } catch (const tf2::TransformException& ex) {
        throw std::runtime_error("Failed to retrieve transformation: " + std::string(ex.what()));
    }
}

void KukaRobot::updateTransforms()
{   
    std::vector<Eigen::Affine3d> new_transformations;

    const std::chrono::duration<double> timeout = std::chrono::seconds(5);

    new_transformations.clear();
    for (const auto &frame : frame_list_)
    {
        try
        {
            // wait until valid transforms are published
            if (!tf_buffer_->canTransform("kuka_base_link", frame, tf2::TimePointZero, tf2::Duration(std::chrono::duration_cast<std::chrono::nanoseconds>(timeout)))) 
            {
                RCLCPP_ERROR(node_->get_logger(), "Timeout waiting for transform for frame %s", frame.c_str());
                throw std::runtime_error("Transform not available within timeout");
            }
            auto transform = tf_buffer_->lookupTransform("kuka_base_link", frame, tf2::TimePointZero);
            Eigen::Affine3d eigen_transform = Eigen::Affine3d::Identity();
            eigen_transform.translation() << transform.transform.translation.x,
                                                transform.transform.translation.y,
                                                transform.transform.translation.z;
            Eigen::Quaterniond q(transform.transform.rotation.w, transform.transform.rotation.x,
                                    transform.transform.rotation.y, transform.transform.rotation.z);
            eigen_transform.rotate(q);
            new_transformations.push_back(eigen_transform);
        }
        catch (const tf2::TransformException &ex)
        {
            RCLCPP_WARN(node_->get_logger(), "Transform error for frame %s: %s", frame.c_str(), ex.what());
            throw;
        }
    }

    // swap buffers
    std::lock_guard<std::mutex> lock(tf_buffer_mutex_);
    tf_write_buffer_ = std::move(new_transformations);
    std::swap(tf_read_buffer_, tf_write_buffer_);

}

bool KukaRobot::initializeKDL()
{
    auto param_client = std::make_shared<rclcpp::SyncParametersClient>(node_, "robot_state_publisher_kuka");

    // Wait for the parameter service to be available
    while (!param_client->wait_for_service(std::chrono::seconds(1)))
    {
        RCLCPP_INFO(rclcpp::get_logger("KukaRobot"), "Waiting for the parameter service...");
    }

    // Retrieve the robot_description parameter
    std::string robot_description;
    try
    {
        robot_description = param_client->get_parameter<std::string>("robot_description_kuka");
    }
    catch (const std::exception &e)
    {
        RCLCPP_ERROR(rclcpp::get_logger("KukaRobot"), "Failed to get parameter 'robot_description': %s", e.what());
        return false;
    }

    // parsing urdf directly from /robot_description topic
    urdf::Model model;
    if (!model.initString(robot_description))
    {
        RCLCPP_ERROR(rclcpp::get_logger("KukaRobot"), "Failed to parse URDF file");
        return false;
    }

    if (!kdl_parser::treeFromUrdfModel(model, kdl_tree_))
    {
        RCLCPP_ERROR(rclcpp::get_logger("KukaRobot"), "Failed to construct KDL tree");
        return false;
    }

    // init main chain
    kdl_tree_.getChain(frame_list_[0], frame_list_[6], kdl_chain_);

    // initialize subchains and solvers for each segment
    for (const auto &segment : kdl_tree_.getSegments())
    {
        const std::string &frame_id = segment.first;

        if (frame_id != frame_list_[0])
        {
            KDL::Chain chain;
            if (kdl_tree_.getChain(frame_list_[0], frame_id, chain))
            {
                kdl_chains_[frame_id] = chain;
            }
            else
            {
                RCLCPP_ERROR(rclcpp::get_logger("KukaRobot"), "Failed to get chain for frame: %s", frame_id.c_str());
                return false;
            }
        }
    }

    RCLCPP_INFO(rclcpp::get_logger("KukaRobot"), "Initialized KDL tree");
    return true;
}

Eigen::MatrixXd KukaRobot::computeJacobian(const std::string &frame_id)
{

    // get chain by name
    std::string forbidden_frame("base_link");
    auto chain_it = kdl_chains_.find(frame_id);
    if (chain_it == kdl_chains_.end() || frame_id.compare(forbidden_frame) == 0)
    {
        RCLCPP_ERROR(rclcpp::get_logger("KukaRobot"), "Failed to find KDL chain or solver for frame: %s", frame_id.c_str());
        return Eigen::MatrixXd::Zero(6, 6);
    }

    // get number of joints for the chain
    KDL::Chain &chain = chain_it->second;
    KDL::JntArray joint_positions(chain.getNrOfJoints());
    for (int i = 0; i < (int)chain.getNrOfJoints(); ++i)
    {
        joint_positions(i) = q_[i];
    }

    // build solvers
    KDL::ChainFkSolverPos_recursive fk_solver(chain);
    KDL::ChainJntToJacSolver jac_solver(chain);
    KDL::Jacobian jacobian(chain.getNrOfJoints());

    jac_solver.JntToJac(joint_positions, jacobian);
    Eigen::MatrixXd jacobian_matrix = jacobian.data;

    return jacobian_matrix;
}

Eigen::MatrixXd KukaRobot::computePseudoInverse(const Eigen::MatrixXd &jacobian)
{

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

    /*
    // -------------------------------------- extra parte mia ------------------------------ //
    // Declare outside the if/else block
    Eigen::MatrixXd statGain;

    Eigen::VectorXd statGainVec;
    if(SigmaPlus.rows() != 9){
        statGainVec = Eigen::VectorXd::Ones(SigmaPlus.rows());
        statGain = statGainVec.asDiagonal();
    }else{
        statGainVec.resize(9); // 9x9 matrix for the static gain
        statGainVec << 1.0, 1.0, 1.0, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01; // static gain vector
        statGain = statGainVec.asDiagonal();
    }
    //std::cout << "cacca: \n" << statGain << "\n\n";
    // -------------------------------------- extra parte mia ------------------------------ //
    //Eigen::MatrixXd SSigmaPlus = (SigmaPlus * statGain) ;
    
    // stampa dimensioni matrici
    //std::cout << " " << SigmaPlus.rows() << "x" << SigmaPlus.cols() << "--" << statGain.rows() << "x" << statGain.cols();
    // std::cout << "V size: " << V.rows() << "x" << V.cols() << "\n";
    // std::cout << "UT size: " << UT.rows() << "x" << UT.cols() << "\n";
    // std::cout << "sGn size: " << statGain.rows() << "x" << statGain.cols() << "\n";

    */

    return V * SigmaPlus * UT;
    
}


Eigen::MatrixXd KukaRobot::attachRigidBodyJacobian(Eigen::MatrixXd link_jacobian, Eigen::Vector3d r_et)
{
    Eigen::MatrixXd rigid_body_jacobian = Eigen::MatrixXd::Zero(6, 6);

    Eigen::Matrix3d r_et_skew;
    r_et_skew << 0, -r_et(2), r_et(1),
        r_et(2), 0, -r_et(0),
        -r_et(1), r_et(0), 0;

    rigid_body_jacobian.block<3, 3>(0, 0) = Eigen::Matrix3d::Identity(3, 3);
    rigid_body_jacobian.block<3, 3>(0, 3) = r_et_skew.transpose();
    rigid_body_jacobian.block<3, 3>(3, 0) = Eigen::Matrix3d::Zero();
    rigid_body_jacobian.block<3, 3>(3, 3) = Eigen::Matrix3d::Identity(3, 3);

    Eigen::MatrixXd full_jacobian = rigid_body_jacobian * link_jacobian;

    return full_jacobian;
}

Eigen::VectorXd KukaRobot::computeCartesianReachingTask(Eigen::Affine3d goal_frame, Eigen::Affine3d ctrl_frame)
{   
    // extract linear and angular 
    Eigen::Vector3d goal_pos = goal_frame.translation();
    Eigen::Quaterniond goal_q(goal_frame.linear());
    Eigen::Vector3d ctrl_pos = ctrl_frame.translation();
    Eigen::Quaterniond ctrl_q(ctrl_frame.linear());

    Eigen::VectorXd error(6);
    error = Eigen::VectorXd::Zero(6);
    double k_pos = 1.0;
    double k_q = 1.0;

    Eigen::Vector3d e_lin = goal_pos - ctrl_pos;

    Eigen::Quaterniond q_error;
    if (goal_q.coeffs().norm() != 0 && ctrl_q.coeffs().norm() != 0)
    {
        if (goal_q.coeffs().dot(ctrl_q.coeffs()) < 0.0)
        {
            ctrl_q.coeffs() << -ctrl_q.coeffs();
        }
        q_error = goal_q.inverse() * ctrl_q;
    }
    Eigen::Vector3d e_ang;
    e_ang << q_error.x(), q_error.y(), q_error.z();
    e_ang << -ctrl_frame.linear() * e_ang;

    // safety check for target frame in origin (for marker-based ik only)
    if (goal_pos.norm() > 0)
    {
        error.head(3) = k_pos * e_lin;
        error.tail(3) = k_q * e_ang;
    }

    return error;
}

// ---------------------------------------------------- getters
std::vector<Eigen::Affine3d> KukaRobot::getTransformations()
{
    std::lock_guard<std::mutex> lock(tf_buffer_mutex_);
    return tf_read_buffer_;
}

Eigen::Affine3d KukaRobot::getGenericTransformation(const std::string& target_frame, const std::string& source_frame)
{
    try {
        geometry_msgs::msg::TransformStamped transform_stamped =
            tf_buffer_->lookupTransform(target_frame, source_frame, tf2::TimePointZero);

         // Extract position
        const auto& translation = transform_stamped.transform.translation;
        Eigen::Vector3d position(translation.x, translation.y, translation.z);

        // Extract quaternion and normalize
        const auto& rotation = transform_stamped.transform.rotation;
        Eigen::Quaterniond quaternion(rotation.w, rotation.x, rotation.y, rotation.z);
        quaternion.normalize();

        // Construct the Affine3d using position and quaternion
        Eigen::Affine3d transform = Eigen::Affine3d::Identity();
        transform.translation() = position;
        transform.linear() = quaternion.toRotationMatrix();

        return transform;

    } catch (const tf2::TransformException& ex) {
        throw std::runtime_error("Failed to retrieve transformation: " + std::string(ex.what()));
    }
}


Eigen::VectorXd KukaRobot::getJointPositions()
{
    return q_;
}

KukaRobot::~KukaRobot()
{
    stop_tf_thread_ = true;
    if (tf_update_thread_.joinable())
    {
        tf_update_thread_.join();
    }
}

// ----------------------------------- controllers
void KukaRobot::runJointControlLoop(Eigen::VectorXd q_err, Eigen::VectorXd q_des)
{
    rclcpp::Rate loop_rate(500);
    float kp = 0.05;
    //std::cout << "Running joint control loop kuka...\n";

    while (rclcpp::ok() && q_err.norm() > 0.1)
    {
        // check joint state
        auto q = getJointPositions();
        std::cout << q << "\n\n";

        // scale velocity according with joint limits
        auto qdot_scaler = getJointLimitsScaler(q);   

        // send joint command 
        Eigen::MatrixXd Kp = Eigen::MatrixXd::Identity(6,6);
        Kp = kp * Kp;
        
        Eigen::VectorXd qdot_des = Eigen::VectorXd::Zero(6);

        // proportional joint controller (add complexity, maybe more useful for the UR10)
        q_err = q_des - q;
        qdot_des = qdot_scaler * Kp * q_err;
        
        // skip first iterations and send command
        updateJointPositionCommand(q, qdot_des);
        
        RCLCPP_INFO(node_->get_logger(), "Joint loop KUKA: joint error norm is %f\r", q_err.norm());
        loop_rate.sleep();
    }
}

void KukaRobot::runCartesianReachingLoop(std::string goal_frame, bool reached_goal)
{
    rclcpp::Rate loop_rate(500);
    float Kp = 0.05;

    while (rclcpp::ok() && reached_goal == false)
    {
            // check tf 
            auto transformations = getTransformations();
            for (const auto &tf : transformations)
            {
                Eigen::Vector3d translation = tf.translation();
            }

            // check joint readings
            auto q = getJointPositions();   

            // compute cartesian reaching task (tool)
            Eigen::Affine3d goal_tf = getGenericTransformation("kuka_base_link", goal_frame);
            Eigen::VectorXd cart_err(6);
            cart_err = computeCartesianReachingTask(goal_tf, transformations.back()); 
            // task stop condition
            if (cart_err.norm() < 0.005) reached_goal = true;

            // compute reaching ik control (tool)
            auto J = computeJacobian("kuka_link_6");
            auto Jpinv = computePseudoInverse(J);
            Eigen::VectorXd qdot_des = Kp * (Jpinv * cart_err);

            // skip first iterations and send command
            updateJointPositionCommand(q, qdot_des);

            RCLCPP_INFO(node_->get_logger(), "Main loop running");
    }
}

// TODO add to ur10e
Eigen::MatrixXd KukaRobot::getJointLimitsScaler(Eigen::VectorXd q)
{
    Eigen::MatrixXd jointLimScaler = Eigen::MatrixXd::Identity(6,6);
    double low_logistic;
    double up_logistic;
    double qdot_scaler;

    for (int i=0; i < q.size(); i++)
    {
        low_logistic = 1/(1 + exp(alpha_low_ * (q_limit_low_[i] - q[i])));
        up_logistic = 1/(1 + exp(alpha_up_ * (q[i] - q_limit_up_[i])));
        qdot_scaler = low_logistic * up_logistic;
        jointLimScaler(i,i) = qdot_scaler;
    }

    return jointLimScaler;
} 

// SIMONE
std::vector<std::string> KukaRobot::getFrameList(){
    return frame_list_;
} 