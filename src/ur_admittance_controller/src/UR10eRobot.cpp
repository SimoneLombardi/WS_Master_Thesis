#include "UR10eRobot.hpp"
#include "RobotInterface.hpp"

// TODO check and change all the links and joint names
void UR10eRobot::initialize(rclcpp::Node::SharedPtr node)
{

    // wait for acquisition to be ready
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    frame_list_ = {"base_link", "shoulder_link", "upper_arm_link", "forearm_link", "wrist_1_link", "wrist_2_link", "tool0"};
    node_ = node;
    tf_buffer_ = std::make_shared<tf2_ros::Buffer>(node_->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
    tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(node_);
    tf_static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(node_);

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
    q_init_ = Eigen::VectorXd::Zero(6);
    joint_names_.resize(6);
    // for joint order mismatch
    ordered_joint_names_ = {"shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint", "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"};


    // initialize IK solvers
    if (!initializeKDL())
    {
        RCLCPP_ERROR(node_->get_logger(), "Failed to initialize KDL");
    }

    // wrist sensor readings
    wrist_wrench_ = Eigen::VectorXd::Zero(6);

    // ------------------------ pubs
    urscript_publisher_ = node_->create_publisher<std_msgs::msg::String>("/urscript_interface/script_command", 10);
    filtered_wrench_publisher_ = node->create_publisher<geometry_msgs::msg::WrenchStamped>("/force_torque_sensor_broadcaster/filteredWrench", 10);

    // ------------------------ subs
    init_joint_state_sub_ = node_->create_subscription<sensor_msgs::msg::JointState>(
        "joint_states",
        rclcpp::QoS(10),
        std::bind(&UR10eRobot::initJointStateCallback, this, std::placeholders::_1));

    // change topic name, I need to handle two robots so different namespaces
    joint_state_sub_ = node_->create_subscription<sensor_msgs::msg::JointState>(
        "joint_states",
        rclcpp::QoS(10),
        std::bind(&UR10eRobot::jointStateCallback, this, std::placeholders::_1));

    // subscrbe to wrist sensor
    wrist_wrench_sub_ = node_->create_subscription<geometry_msgs::msg::WrenchStamped>(
      "force_torque_sensor_broadcaster/wrench", 
      rclcpp::QoS(10),                          
      std::bind(&UR10eRobot::wristWrenchCallback, this, std::placeholders::_1)
    );

    // start tf updating
    stop_tf_thread_ = false;
    tf_update_thread_ = std::thread(&UR10eRobot::tfUpdateLoop, this);

    RCLCPP_INFO(node_->get_logger(), "UR10eRobot robot interface initialized");
}

/**
     * @brief hanging callback to wait for the first meaningful state reading
*/
// TODO Initial state is zero for few samples, need to neglect that.
void UR10eRobot::initJointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
{
    // map joint names to indexes
    std::unordered_map<std::string, size_t> name_to_index;
    for (size_t i = 0; i < msg->name.size(); ++i)
    {
        name_to_index[msg->name[i]] = i;
    }

    if (!initial_state_received_)
    {

        // Store initial joint configuration or state
        for (size_t i = 0; i < ordered_joint_names_.size(); ++i)
        {
            const std::string &joint_name = ordered_joint_names_[i];
            if (name_to_index.find(joint_name) != name_to_index.end())
            {
                size_t index = name_to_index[joint_name];
                q_init_[i] = msg->position[index];
            }
        }
        RCLCPP_INFO(rclcpp::get_logger("UR10eRobot"), "sampled initial state");
        initial_state_received_ = true;

        // unsubscribe callback
        init_joint_state_sub_.reset();
    }
}

/**
     * @brief Retrieve the joint state message and fills joint structures
*/
// TODO Check if I need to send control signal directly from here or there is a more structured approach
void UR10eRobot::jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
{

    // wait for the initial state to be sampled
    if (!initial_state_received_)
    {
        RCLCPP_WARN(rclcpp::get_logger("UR10eRobot"), "Waiting for initial state...");
        return;
    }

    // re-arranging joint names to correct sequence
    std::unordered_map<std::string, size_t> name_to_index;
    for (size_t i = 0; i < msg->name.size(); ++i)
    {
        name_to_index[msg->name[i]] = i;
    }

    for (size_t i = 0; i < ordered_joint_names_.size(); ++i)
    {
        const std::string &joint_name = ordered_joint_names_[i];
        if (name_to_index.find(joint_name) != name_to_index.end())
        {
            size_t index = name_to_index[joint_name];
            q_[i] = msg->position[index];
            qdot_[i] = msg->velocity[index];
            q_efforts_[i] = msg->effort[index];
            joint_names_[i] = joint_name;
        }
    }
}

void UR10eRobot::tfUpdateLoop()
{
    rclcpp::Rate loop_rate(10); 

    while (!stop_tf_thread_ && rclcpp::ok())
    {
        updateTransforms(); 
        loop_rate.sleep();
    }
}

void UR10eRobot::updateTransforms()
{
    std::vector<Eigen::Affine3d> new_transformations;

    new_transformations.clear();
    for (const auto &frame : frame_list_)
    {
        try
        {
            auto transform = tf_buffer_->lookupTransform("base_link", frame, tf2::TimePointZero);
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
        }
    }

    // swap buffers
    std::lock_guard<std::mutex> lock(tf_buffer_mutex_);
    tf_write_buffer_ = std::move(new_transformations);
    std::swap(tf_read_buffer_, tf_write_buffer_);

}

Eigen::Affine3d UR10eRobot::getGenericTransformation(const std::string& target_frame, const std::string& source_frame)
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

void UR10eRobot::sendJointVelocityCommand(Eigen::VectorXd qdot_des)
{
    // ur joint interface parameters
    float target_acceleration = 1; // rad/s^2
    float control_timeout = 0.05;  // sec

    // build string message
    auto speedj_msg = std_msgs::msg::String();
    std::string control_command = std::string("speedj([");
    for (int i = 0; i < qdot_des.size(); i++)
    {
        std::string q_tmp = std::to_string(qdot_des(i));
        std::string separator;
        if (i >= 5)
        {
            separator = std::string("]");
        }
        else
        {
            separator = std::string(",");
        }
        control_command = control_command + q_tmp + separator;
    }
    control_command = control_command + std::string(",") +
                    std::to_string(target_acceleration) +
                    std::string(",") +
                    std::to_string(control_timeout) +
                    std::string(")");
    speedj_msg.data = control_command;
    urscript_publisher_->publish(speedj_msg);
}

void UR10eRobot::publishFilteredWrench(Eigen::VectorXd filt_wrench)
{
    //float scaling = 0.1; 
    //filt_wrench = scaling * filt_wrench;
    auto filt_wrench_msg = geometry_msgs::msg::WrenchStamped();
    filt_wrench_msg.header.stamp = node_->get_clock()->now();
    filt_wrench_msg.header.frame_id = "tool0";
    filt_wrench_msg.wrench.force.x = filt_wrench[0];
    filt_wrench_msg.wrench.force.y = filt_wrench[1];
    filt_wrench_msg.wrench.force.z = filt_wrench[2];
    filt_wrench_msg.wrench.torque.x = filt_wrench[3];
    filt_wrench_msg.wrench.torque.y = filt_wrench[4];
    filt_wrench_msg.wrench.torque.z = filt_wrench[5];

    filtered_wrench_publisher_->publish(filt_wrench_msg);
}

// ---------------------------------------------------- inverse kinematics

bool UR10eRobot::initializeKDL()
{
    auto param_client = std::make_shared<rclcpp::SyncParametersClient>(node_, "robot_state_publisher");

    // Wait for the parameter service to be available
    int timeout_steps = 0;
    while (!param_client->wait_for_service(std::chrono::seconds(1)) && timeout_steps < 20)
    {
        RCLCPP_INFO(rclcpp::get_logger("UR10eRobot"), "Waiting for the parameter service...");
        timeout_steps++;
    }

    // Retrieve the robot_description parameter
    std::string robot_description;
    try
    {
        robot_description = param_client->get_parameter<std::string>("robot_description");
    }
    catch (const std::exception &e)
    {
        RCLCPP_ERROR(rclcpp::get_logger("UR10eRobot"), "Failed to get parameter 'robot_description': %s", e.what());
        return false;
    }

    // parsing urdf directly from /robot_description topic
    urdf::Model model;
    if (!model.initString(robot_description))
    {
        RCLCPP_ERROR(rclcpp::get_logger("UR10eRobot"), "Failed to parse URDF file");
        return false;
    }

    if (!kdl_parser::treeFromUrdfModel(model, kdl_tree_))
    {
        RCLCPP_ERROR(rclcpp::get_logger("UR10eRobot"), "Failed to construct KDL tree");
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
                RCLCPP_ERROR(rclcpp::get_logger("UR10eRobot"), "Failed to get chain for frame: %s", frame_id.c_str());
                return false;
            }
        }
    }

    return true;
}

Eigen::MatrixXd UR10eRobot::computeJacobian(const std::string &frame_id)
{

    // get chain by name
    std::string forbidden_frame("base_link");
    auto chain_it = kdl_chains_.find(frame_id);
    if (chain_it == kdl_chains_.end() || frame_id.compare(forbidden_frame) == 0)
    {
        RCLCPP_ERROR(rclcpp::get_logger("UR10eRobot"), "Failed to find KDL chain or solver for frame: %s", frame_id.c_str());
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

Eigen::MatrixXd UR10eRobot::computePseudoInverse(const Eigen::MatrixXd &jacobian)
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

    return V * SigmaPlus * UT;
}

Eigen::MatrixXd UR10eRobot::attachRigidBodyJacobian(Eigen::MatrixXd link_jacobian, Eigen::Vector3d r_et)
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

Eigen::VectorXd UR10eRobot::computeCartesianReachingTask(Eigen::Affine3d goal_frame, Eigen::Affine3d ctrl_frame)
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


// wrist f/t sensor readings
void UR10eRobot::wristWrenchCallback(const geometry_msgs::msg::WrenchStamped::SharedPtr msg)
{
    wrist_wrench_(0) = msg->wrench.force.x;
    wrist_wrench_(1) = msg->wrench.force.y;
    wrist_wrench_(2) = msg->wrench.force.z;
    wrist_wrench_(3) = msg->wrench.torque.x;
    wrist_wrench_(4) = msg->wrench.torque.y;
    wrist_wrench_(5) = msg->wrench.torque.z;
}

// force/torque zeroing (reset)
void UR10eRobot::zeroFtSensor()
{
    // build string message
    auto zeroft_msg = std_msgs::msg::String();
    std::string ft_sensor_reset_command = std::string("zero_ftsensor()");
    zeroft_msg.data = ft_sensor_reset_command;
    urscript_publisher_->publish(zeroft_msg);
}

// ---------------------------------------------------- getters
std::vector<Eigen::Affine3d> UR10eRobot::getTransformations()
{
    std::lock_guard<std::mutex> lock(tf_buffer_mutex_);
    return tf_read_buffer_;
}

Eigen::VectorXd UR10eRobot::getJointPositions()
{
    return q_;
}

Eigen::VectorXd UR10eRobot::getWristWrench()
{
    return wrist_wrench_;
}


UR10eRobot::~UR10eRobot()
{

    // stop tf updater
    stop_tf_thread_ = true;
    if (tf_update_thread_.joinable())
    {
        tf_update_thread_.join();
    }
}
