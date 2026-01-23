#include "UR10eRobot.hpp"
#include "RobotInterface.hpp"

using namespace std::chrono_literals;

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
    control_task_viz_publisher_ = node->create_publisher<visualization_msgs::msg::Marker>("/uc1_viz/control_task", 10);
    control_task_base_viz_publisher_ = node->create_publisher<visualization_msgs::msg::Marker>("/uc1_viz/control_task_base", 10);

    // ------------------------ subs
    init_joint_state_sub_ = node_->create_subscription<sensor_msgs::msg::JointState>(
        "joint_states_ur10",
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

    // subscribe to proximity tasks
    proximity_tasks_sub_ = node_->create_subscription<uc1_robot_perception::msg::ProximityTaskArray>(
      "proximity_task_control",
      10,
      std::bind(&UR10eRobot::proximityTasksCallback, this, std::placeholders::_1)
    );

    tactile_tasks_sub_ = node_->create_subscription<uc1_robot_perception::msg::ContactArray>(
      "contacts",
      10,
      std::bind(&UR10eRobot::tactileTasksCallback, this, std::placeholders::_1)
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
    // funizione per errore robot destrcription non trovato
    while(rclcpp::ok()){
        try{
            robot_description = param_client->get_parameter<std::string>("robot_description");
            RCLCPP_INFO(rclcpp::get_logger("UR10eRobot"), "Successfully retrieved robot_description parameter, LENGHT: %zu", robot_description.size());
            break;
        }catch(const std::exception &e){
            RCLCPP_INFO(rclcpp::get_logger("UR10eRobot"), "waiting for robot description parameter...': %s", e.what());
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    }
    /*
    try
    {
        robot_description = param_client->get_parameter<std::string>("robot_description");
    }
    catch (const std::exception &e)
    {
        RCLCPP_ERROR(rclcpp::get_logger("UR10eRobot"), "Failed to get parameter 'robot_description': %s", e.what());
        return false;
    }*/

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

void UR10eRobot::setDynamicGravity()
{
    // extract z axis from kuka flange
    Eigen::Affine3d flange_tf = getGenericTransformation("kuka_base_link", "kuka_link_6");
    Eigen::Matrix3d flange_rotm = flange_tf.rotation();
    Eigen::Vector3d flange_z = flange_rotm.col(2);

    // scale earth gravity 
    Eigen::Vector3d gravity_ur = 9.82 * flange_z;

    // send urscript command
    auto dynamic_gravity_msg = std_msgs::msg::String();
    std::string dynamic_gravity_command = std::string("set_gravity([");
    for (int i = 0; i < gravity_ur.size(); i++)
    {
        std::string item = std::to_string(gravity_ur(i));
        std::string separator;
        separator = std::string(",");

        dynamic_gravity_command = dynamic_gravity_command + item + separator;
    }
    dynamic_gravity_command.pop_back();
    dynamic_gravity_command = dynamic_gravity_command + std::string("])");
    
    dynamic_gravity_msg.data = dynamic_gravity_command;
    urscript_publisher_->publish(dynamic_gravity_msg);

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

// ------------------------------------------------- controllers
void UR10eRobot::runJointControlLoop(Eigen::VectorXd q_err, Eigen::VectorXd q_des)
{
    rclcpp::Rate loop_rate(100);
    float kp = 0.1;
    //std::cout << "Running joint control loop ur10..." << std::endl;

    while (rclcpp::ok() && q_err.norm() > 0.05)
    {
        // update gravity
        //setDynamicGravity(); 

        // check joint state
        auto q = getJointPositions();

        //std::cout << q << std::endl;

        // send joint command 
        float kp = 0.2;
        Eigen::MatrixXd Kp = Eigen::MatrixXd::Identity(6,6);
        Kp = kp * Kp;
        
        Eigen::VectorXd qdot_des = Eigen::VectorXd::Zero(6);

        // proportional joint controller
        q_err = q_des - q;
        qdot_des = Kp * q_err;

        // skip first iterations and send command
        if (q.norm() != 0) sendJointVelocityCommand(qdot_des);
        
        //RCLCPP_INFO(node_->get_logger(), "Joint loop UR10: joint error norm is %f\r", q_err.norm());
        loop_rate.sleep();
    }
}

void UR10eRobot::runCartesianReachingLoop(std::string goal_frame, bool reached_goal)
{
    rclcpp::Rate loop_rate(100);
    float Kp = 0.05;

    while (rclcpp::ok() && reached_goal == false)
    {
        // check robot state
        auto transformations = getTransformations();

        // check joint state
        auto q = getJointPositions();

        // compute cartesian reaching task (tool)
        Eigen::Affine3d goal_tf = getGenericTransformation("base_link", "ik_reach_goal");
        Eigen::VectorXd cart_err(6);
        cart_err = computeCartesianReachingTask(goal_tf, transformations.back()); // goal and tool frames

        // task stop condition
        if (cart_err.norm() < 0.02) reached_goal = true;

        //Eigen::Affine3d goal_tf = ur10e_robot->getGenericTransformation("base_link", "forearm_reach_goal");
        //Eigen::VectorXd cart_err(6);
        //cart_err = ur10e_robot->computeCartesianReachingTask(goal_tf, transformations[3]); // goal and tool frames
        //cart_err.tail(3) = Eigen::Vector3d::Zero();
        
        // compute reaching ik control (tool)
        float Kp = 0.5;
        auto J = computeJacobian("tool0");
        auto Jpinv = computePseudoInverse(J);
        Eigen::VectorXd qdot_des = Kp * (Jpinv * cart_err);

        // compute reaching ik control (shoulder, for basic avoidance)
        // auto J = ur10e_robot->computeJacobian("forearm_link");
        // auto Jpinv = ur10e_robot->computePseudoInverse(J);
        // Eigen::VectorXd qdot_des(6);
        // qdot_des << 0, 0, 0, 0, 0, 0;
        // qdot_des.head(3) = Kp * (Jpinv * cart_err);
        // std::cout << qdot_des << std::endl;

        // skip first iterations and send command
        sendJointVelocityCommand(qdot_des);
        loop_rate.sleep();
    }
}

void UR10eRobot::runProximityControlLoop(std::string goal_frame, bool reached_goal)
{
    rclcpp::Rate loop_rate(100);
    float Kp = 0.05;

    while (rclcpp::ok() && reached_goal == false)
    {
        // check robot state
        auto transformations = getTransformations();

        // check joint state
        auto q = getJointPositions();
        
        // swap task buffers
        swapProximityBuffers();
        
        // ------------------------------- sensor-based task
        // get closest sensor-based task (when I add the multi-point, remove this)
        auto control_task_msg = getMinDistTask(proxy_front_tasks_);

        // check task correctness
        displayProximityTask(control_task_msg);

        // build KUKA admittance task (to be published)
        Eigen::Vector3d robot_base_task = projectTaskOnRobotBase(
                                            control_task_msg.min_point_robot,
                                            control_task_msg.min_point_vector,
                                            control_task_msg.distance,
                                            control_task_msg.link_id,
                                            "base_link");

        // DEBUG force task visualization - main task
        Eigen::Vector3d sensor_frame_task_point(control_task_msg.min_point_robot.x,
                                                control_task_msg.min_point_robot.y,
                                                control_task_msg.min_point_robot.z);
        Eigen::Vector3d sensor_frame_task_vec(control_task_msg.min_point_vector.x,
                                                control_task_msg.min_point_vector.y,
                                                control_task_msg.min_point_vector.z);    
        sensor_frame_task_vec = control_task_msg.distance * sensor_frame_task_vec;                                     
        publishArrowMarker(sensor_frame_task_point,
                            sensor_frame_task_vec,
                            control_task_msg.link_id,
                            "task_marker",
                            1,
                            control_task_viz_publisher_);

        // DEBUG force task visualization - projected task
        publishArrowMarker(Eigen::Vector3d(0, 0, 0),
                            robot_base_task,
                            "base_link",
                            "task_marker_base",
                            20,
                            control_task_base_viz_publisher_);
                            

        // min point msg to eigen
        Eigen::Vector3d control_point;
        control_point << control_task_msg.min_point_robot.x, control_task_msg.min_point_robot.y, control_task_msg.min_point_robot.z;

        // get task jacobian (TODO vectorize)
        auto J_avoidance = computeAvoidanceJacobian(control_point, control_task_msg.link_id);

        // get task velocity
        Eigen::VectorXd xdot_avoidance(6);
        float alpha_avoidance;
        xdot_avoidance = computeProximityAvoidance(control_task_msg, alpha_avoidance);

        
        // -------------------------------------------------

        // compute cartesian reaching task (tool)
        Eigen::Affine3d goal_tf = getGenericTransformation("base_link", "ik_reach_goal");
        Eigen::VectorXd xdot_reach(6);
        xdot_reach = computeCartesianReachingTask(goal_tf, transformations.back()); // goal and tool frames

        // task stop condition
        if (xdot_reach.norm() < 0.02) reached_goal = true;
        
        // compute reaching ik control (tool)
        float Kp = 0.1; // low for testing
        float alpha_reach = Kp;
        auto J_reach = computeJacobian("tool0");
        auto Jpinv = computePseudoInverse(J_reach);
        //Eigen::VectorXd qdot_des = Kp * (Jpinv * xdot_reach);
        Eigen::VectorXd qdot_des = Eigen::VectorXd::Zero(6);

        // ----------------------------------------------- prioritized control
        // stack tasks (all avoidance tasks first, then reaching as last)
        std::vector<Eigen::MatrixXd> J_tasks; 
        std::vector<Eigen::VectorXd> xdot_tasks;
        std::vector<float> alpha_tasks;
        J_tasks.push_back(J_avoidance); J_tasks.push_back(J_reach); 
        xdot_tasks.push_back(xdot_avoidance); xdot_tasks.push_back(xdot_reach);
        alpha_tasks.push_back(0.5*alpha_avoidance); alpha_tasks.push_back(alpha_reach);

        // compute qdots from TPIK
        qdot_des = ComputePrioritizedControlLawDLS(J_tasks, xdot_tasks, alpha_tasks, control_task_msg.link_id);

        // skip first iterations and send command
        //qdot_des.setZero(); // DEBUG
        sendJointVelocityCommand(qdot_des);
        loop_rate.sleep();
    }
}

void UR10eRobot::runTactileControlLoop(std::string goal_frame, bool reached_goal)
{
    rclcpp::Rate loop_rate(100);
    float Kp = 0.05;

    while (rclcpp::ok() && reached_goal == false)
    {
        // check robot state
        auto transformations = getTransformations();

        // check joint state
        auto q = getJointPositions();
        
        // swap task buffers
        swapTactileBuffers();
        
        // ------------------------------- sensor-based task
        // get closest sensor-based task (when I add the multi-point, remove this)
        auto control_task_msg = getMaxForceTask(tactile_front_tasks_);

        std::cout << "Message force intensity: " << control_task_msg.contact_intensity << std:: endl;

        // check task correctness
        //displayTactileTask(control_task_msg);

        // min point msg to eigen
        Eigen::Vector3d control_point;
        control_point << control_task_msg.contact_location.x, control_task_msg.contact_location.y, control_task_msg.contact_location.z;

        // get task jacobian (TODO vectorize)
        auto J_avoidance = computeAvoidanceJacobian(control_point, control_task_msg.reference_frame);

        // get task velocity
        Eigen::VectorXd xdot_avoidance(6);
        float alpha_avoidance;
        xdot_avoidance = computeTactileAvoidance(control_task_msg, alpha_avoidance);
        
        // -------------------------------------------------

        // compute cartesian reaching task (tool)
        Eigen::Affine3d goal_tf = getGenericTransformation("base_link", "ik_reach_goal");
        Eigen::VectorXd xdot_reach(6);
        xdot_reach = computeCartesianReachingTask(goal_tf, transformations.back()); // goal and tool frames

        // task stop condition
        if (xdot_reach.norm() < 0.02) reached_goal = true;
        
        // compute reaching ik control (tool)
        //float Kp = 0.1; // low for testing
        float alpha_reach = Kp;
        auto J_reach = computeJacobian("tool0");
        auto Jpinv = computePseudoInverse(J_reach);
        //Eigen::VectorXd qdot_des = Kp * (Jpinv * xdot_reach);
        Eigen::VectorXd qdot_des = Eigen::VectorXd::Zero(6);

        // ----------------------------------------------- prioritized control
        // stack tasks (all avoidance tasks first, then reaching as last)
        std::vector<Eigen::MatrixXd> J_tasks; 
        std::vector<Eigen::VectorXd> xdot_tasks;
        std::vector<float> alpha_tasks;
        J_tasks.push_back(J_avoidance); J_tasks.push_back(J_reach); 
        xdot_tasks.push_back(xdot_avoidance); xdot_tasks.push_back(xdot_reach);
        alpha_tasks.push_back(alpha_avoidance); alpha_tasks.push_back(alpha_reach);

        // compute qdots from TPIK
        qdot_des = ComputePrioritizedControlLawDLS(J_tasks, xdot_tasks, alpha_tasks, control_task_msg.reference_frame);

        // skip first iterations and send command
        //qdot_des.setZero(); // DEBUG
        sendJointVelocityCommand(qdot_des);
        loop_rate.sleep();
    }
}

//-----------------------------------  task data storage callbacks

// ------------------ Proximity
void UR10eRobot::proximityTasksCallback(const uc1_robot_perception::msg::ProximityTaskArray::SharedPtr msg)
{
    std::lock_guard<std::mutex> lock(proxy_buffer_mutex_);
    proxy_back_tasks_ = *msg;
    proxy_new_data_available_ = true;
}

void UR10eRobot::swapProximityBuffers()
{
  std::lock_guard<std::mutex> lock(proxy_buffer_mutex_);
  if(proxy_new_data_available_) {
    proxy_front_tasks_ = proxy_back_tasks_;
    proxy_new_data_available_ = false;
  }
}

// needed for legacy single-point controller
uc1_robot_perception::msg::ProximityTask UR10eRobot::getMinDistTask(const uc1_robot_perception::msg::ProximityTaskArray & tasks_msg)
{
  if (tasks_msg.proximity_tasks.empty()) {
    RCLCPP_WARN(rclcpp::get_logger("getMinDistTask"), "No proximity tasks available!");
    // fill dummy task on base_link, it will be filtered out anyway
    uc1_robot_perception::msg::ProximityTask dummy_task;
    dummy_task.min_point_robot.x = 0.0;
    dummy_task.min_point_robot.y = 0.0;
    dummy_task.min_point_robot.z = 0.0;
    dummy_task.min_point_vector.x = 0.0;
    dummy_task.min_point_vector.y = 0.0;
    dummy_task.min_point_vector.z = 0.0;
    dummy_task.distance = 0.0;
    dummy_task.link_id = "base_link";

    return dummy_task;
  }

  float min_distance = std::numeric_limits<float>::max();
  uc1_robot_perception::msg::ProximityTask selected_task;

  // find minimum distance task among all links
  for (const auto & task : tasks_msg.proximity_tasks) {
    if (task.distance < min_distance) {
      min_distance = task.distance;
      selected_task = task;
    }
  }
  return selected_task;
}

void UR10eRobot::displayProximityTask(const uc1_robot_perception::msg::ProximityTask & task)
{
  std::cout << "----------------------------------------" << std::endl;
  std::cout << "Control Task for Link: " << task.link_id << std::endl;
  std::cout << "Distance: " << task.distance << " m" << std::endl;
  std::cout << "Min Point Robot: (" 
            << task.min_point_robot.x << ", " 
            << task.min_point_robot.y << ", " 
            << task.min_point_robot.z << ")" << std::endl;
  std::cout << "Min Point Vector: (" 
            << task.min_point_vector.x << ", " 
            << task.min_point_vector.y << ", " 
            << task.min_point_vector.z << ")" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
}

// ---------------------- Tactile

void UR10eRobot::tactileTasksCallback(const uc1_robot_perception::msg::ContactArray::SharedPtr msg)
{
    std::lock_guard<std::mutex> lock(tactile_buffer_mutex_);
    tactile_back_tasks_ = *msg;
    tactile_new_data_available_ = true;
}

void UR10eRobot::swapTactileBuffers()
{
  std::lock_guard<std::mutex> lock(tactile_buffer_mutex_);
  if(tactile_new_data_available_) {
    tactile_front_tasks_ = tactile_back_tasks_;
    tactile_new_data_available_ = false;
  }
}

// TODO need to add multiple contact tasks for the highest priority level
uc1_robot_perception::msg::Contact UR10eRobot::getMaxForceTask(const uc1_robot_perception::msg::ContactArray & tasks_msg)
{
  if (tasks_msg.contacts.empty()) {
    RCLCPP_WARN(rclcpp::get_logger("getMaxForceTask"), "No contact tasks available!");
    // fill dummy task on base_link, it will be filtered out anyway
    uc1_robot_perception::msg::Contact dummy_task;
    dummy_task.contact_location.x = 0.0;
    dummy_task.contact_location.y = 0.0;
    dummy_task.contact_location.z = 0.0;
    dummy_task.contact_normal.x = 0.0;
    dummy_task.contact_normal.y = 0.0;
    dummy_task.contact_normal.z = 0.0;
    dummy_task.contact_intensity = 0.0;
    dummy_task.reference_frame = "base_link";

    return dummy_task;
  }

  float max_force = std::numeric_limits<float>::max();  // default upper bound
  uc1_robot_perception::msg::Contact selected_task;

  // find minimum distance task among all links
  for (const auto & task : tasks_msg.contacts) {
    if (task.contact_intensity < max_force) {
      max_force = task.contact_intensity;
      selected_task = task;
    }
  }
  return selected_task;
}

void UR10eRobot::displayTactileTask(const uc1_robot_perception::msg::Contact & task)
{
  std::cout << "----------------------------------------" << std::endl;
  std::cout << "Control Task for Link: " << task.reference_frame << std::endl;
  std::cout << "Force: " << task.contact_intensity << " N" << std::endl;
  std::cout << "Min Point Robot: (" 
            << task.contact_location.x << ", " 
            << task.contact_location.y << ", " 
            << task.contact_location.z << ")" << std::endl;
  std::cout << "Min Point Vector: (" 
            << task.contact_normal.x << ", " 
            << task.contact_normal.y << ", " 
            << task.contact_normal.z << ")" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
}

// --------------------- Controllers
Eigen::MatrixXd UR10eRobot::computeAvoidanceJacobian(Eigen::Vector3d min_point, std::string frame_id)
{
    // get target link jacobian (for link's frame)
    Eigen::MatrixXd link_J = computeJacobian(frame_id);
    Eigen::MatrixXd link_J_avoidance = link_J;

    // get target link tf
    Eigen::Affine3d link_tf = getGenericTransformation("base_link", frame_id);

    Eigen::Vector3d distance_link_min;
    distance_link_min << min_point - link_tf.translation();
    if ( link_J.isZero()) {
        link_J_avoidance.setZero();
    }
    else {
        for (int i=0; i<link_J.cols(); ++i) {
            link_J_avoidance.col(i)=link_J.col(i);
        }
    }
    link_J_avoidance = attachRigidBodyJacobian( link_J_avoidance, distance_link_min);
    return link_J_avoidance;
}

Eigen::VectorXd UR10eRobot::computeProximityAvoidance(const uc1_robot_perception::msg::ProximityTask & task, float & activation)
{
    Eigen::VectorXd avoidance_task(6);
    Eigen::VectorXd mindist_vector(6); 

    mindist_vector << task.min_point_vector.x, 
                        task.min_point_vector.y, 
                        task.min_point_vector.z,
                        0.0,
                        0.0,
                        0.0;

    double minimum_dist = 0.2; // min threshold for activation function being = 1
    double alfa = 0.25;        // max threshold added to min, for activation function being = 0

    double min_avoidance = (minimum_dist + alfa) - task.distance;
    //std::cout<<"The mindist is: "<<vec_min_dist.norm()<<"\n\n";

    // build the cartesian avoidance task
    if (task.distance < minimum_dist + alfa)
        avoidance_task = -task.distance * mindist_vector;
    else
        avoidance_task << 0, 0, 0, 0, 0, 0;

    // compute activation
    activation = DecreasingBellShapedFunction(minimum_dist, minimum_dist + alfa, 0, 1, task.distance);

    return avoidance_task;
}

Eigen::VectorXd UR10eRobot::computeTactileAvoidance(const uc1_robot_perception::msg::Contact & task, float & activation)
{
    Eigen::VectorXd avoidance_task(6); 
    Eigen::VectorXd force_vector(6); 

    force_vector << task.contact_normal.x, 
                    task.contact_normal.y, 
                    task.contact_normal.z,
                        0.0,
                        0.0,
                        0.0;

    double minimum_force = 0.5; // force threshold for activation function being = 1
    double alfa = 1;        // max threshold added to min, for activation function being = 0

    double min_avoidance = (minimum_force + alfa) - task.contact_intensity;
    //std::cout<<"The mindist is: "<<vec_min_dist.norm()<<"\n\n";

    // build the cartesian avoidance task
    /*
    if (task.contact_intensity > minimum_force + alfa)
        avoidance_task = task.contact_intensity * force_vector;
    else
        avoidance_task << 0, 0, 0, 0, 0, 0;
    */
    avoidance_task = -task.contact_intensity * force_vector;

    // compute activation
    activation = IncreasingBellShapedFunction(minimum_force, minimum_force + alfa, 0, 1, task.contact_intensity);
    std::cout << "Activation: " << activation << std::endl;

    return avoidance_task;
}

// task priority law (now for single avoidance task, needs to be vectorized)
Eigen::VectorXd UR10eRobot::ComputePrioritizedControlLawDLS(std::vector<Eigen::MatrixXd> J_tasks, 
                                                            std::vector<Eigen::VectorXd> tasks, 
                                                            std::vector<float> alpha,
                                                            std::string link_id)
{
    // base link task to null, since no jacobian exists
    if(link_id == "base_link")
    {
        tasks[0].setZero();
        J_tasks[0].setZero();
    }

    // naive resize for avoidance jacobian (TODO extend for multiple tasks)
    J_tasks[0].conservativeResize(6, 6);
    J_tasks[0].block(0, 3, 6, 3).setZero();

    // J_tasks : Task Jacobians
    // tasks : vector of tasks expressed as velocities in cartesian space
    // alpha : activation functions/thresholds
    Eigen::VectorXd q_dot(6);

    Eigen::VectorXd h, r(6), z(6);
    Eigen::MatrixXd G, G_h, Q, T, pseudo_inv;

    // Init
    r << 0, 0, 0, 0, 0, 0;
    z << 0, 0, 0, 0, 0, 0;
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(6, 6);
    Q = I;

    // for (size_t i = 0; i < J_tasks.size(); i++)
    // {
    //     std::cout << J_tasks[i] << "\n";
    //     std::cout << tasks[i] << "\n\n";
    // }

    for (size_t i = 0; i < J_tasks.size(); i++)
    {
        h = alpha[i] * tasks[i];
        //h = tasks[i];
        G = alpha[i] * J_tasks[i];
        //G = J_tasks[i];
        G_h = G * Q;
        //ss << "The initial matrix is: \n "<< alpha[i] <<"\n";
        pseudo_inv = computePseudoInverse(G_h);
        //ss << "The pseudoinv is:\n " << G_h << "\n";
        //RCLCPP_INFO(this->get_logger(), "%s", ss.str().c_str());
        T = (I - Q * pseudo_inv * G);
        r = T * r + Q * pseudo_inv * h;
        Q = Q * (I - pseudo_inv * G_h);
    }

    q_dot = r + Q * z;

    return q_dot;
}

// activation function
double UR10eRobot::DecreasingBellShapedFunction(double xmin, double xmax, double ymin, double ymax, double x)
{
    double y;
    if (x <= xmin)
        y = ymax;
    else if (x >= xmax)
        y = ymin;
    else
    {
        double cosarg = (x - xmin) * M_PI / (xmax - xmin);
        y = (ymax - ymin) * (0.5 * cos(cosarg) + 0.5) + ymin;
    }

    return y;
}

double UR10eRobot::IncreasingBellShapedFunction(double xmin, double xmax, double ymin, double ymax, double x)
{
    double y;
    if (x <= xmin)
        y = ymin;
    else if (x >= xmax)
        y = ymax;
    else
    {
        double cosarg = (x - xmin) * M_PI / (xmax - xmin);
        y = (ymax - ymin) * (0.5 * (1.0 - cos(cosarg))) + ymin;
    }
    return y;
}

Eigen::Vector3d UR10eRobot::projectTaskOnRobotBase(
    const geometry_msgs::msg::Vector3& sensor_position,
    const geometry_msgs::msg::Vector3& sensor_z_normal,
    float measured_force,
    const std::string& link_frame,
    const std::string& base_frame)
{
    // build sensor rotation wrt local frame
    Eigen::Vector3d z_axis(sensor_z_normal.x, sensor_z_normal.y, sensor_z_normal.z);
    z_axis.normalize();
    Eigen::Vector3d arbitrary_axis(1, 0, 0);
    if (z_axis.cross(arbitrary_axis).norm() < 1e-3) {
        arbitrary_axis = Eigen::Vector3d(0, 1, 0);
    }
    Eigen::Vector3d x_axis = arbitrary_axis.cross(z_axis).normalized();
    Eigen::Vector3d y_axis = z_axis.cross(x_axis).normalized();

    Eigen::Matrix3d R_link_sensor;
    R_link_sensor.col(0) = x_axis;
    R_link_sensor.col(1) = y_axis;
    R_link_sensor.col(2) = z_axis;

    // get rotation of target link in base frame
    geometry_msgs::msg::TransformStamped tf_base_link;
    try {
        tf_base_link = tf_buffer_->lookupTransform(base_frame, link_frame, tf2::TimePointZero);
    } catch (tf2::TransformException &ex) {
        RCLCPP_WARN(rclcpp::get_logger("computeProjectedForce"), "%s", ex.what());
        return Eigen::Vector3d::Zero();
    }
    tf2::Quaternion q(
        tf_base_link.transform.rotation.x,
        tf_base_link.transform.rotation.y,
        tf_base_link.transform.rotation.z,
        tf_base_link.transform.rotation.w);
    Eigen::Matrix3d R_base_link = Eigen::Quaterniond(q.w(), q.x(), q.y(), q.z()).toRotationMatrix();

    // rotation from robot base to sensor
    Eigen::Matrix3d R_base_sensor = R_base_link * R_link_sensor;

    // rotate force to robot base and null orthogonal component
    Eigen::Vector3d force_sensor(sensor_z_normal.x * measured_force, 
                                    sensor_z_normal.y * measured_force, 
                                    sensor_z_normal.z * measured_force);
    Eigen::Vector3d force_base = R_base_sensor * force_sensor;

    force_base.z() = 0.0; 

    return force_base;
}

void UR10eRobot::publishArrowMarker(
    const Eigen::Vector3d& origin,
    const Eigen::Vector3d& vector,
    const std::string& frame_id,
    const std::string& ns,
    int id,
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr publisher)
{
    visualization_msgs::msg::Marker marker;
    marker.header.frame_id = frame_id;
    marker.header.stamp = rclcpp::Clock().now();
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

    marker.points.push_back(start);
    marker.points.push_back(end);

    marker.scale.x = 0.02;  // shaft diameter
    marker.scale.y = 0.04;  // head diameter
    marker.scale.z = 0.1;   // head length

    marker.color.a = 1.0;
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;

    publisher->publish(marker);
}

// SIMONE
std::vector<std::string> UR10eRobot::getFrameList(){
    return frame_list_;
} 

