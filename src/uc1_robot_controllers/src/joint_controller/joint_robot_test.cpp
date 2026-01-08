#include "JointRobot.hpp"
#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"
#include "TfGoalBroadcaster.hpp"


#include <csignal>
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto joint_robot = std::make_shared<JointRobot>();
    auto joint_robot_node = std::make_shared<rclcpp::Node>("joint_robot_node");
    
    auto kuka_node = std::make_shared<rclcpp::Node>("kuka_robot_node");
    auto ur10_node = std::make_shared<rclcpp::Node>("ur10_robot_node");

    //auto jointRobot_broadcaster = std::make_shared<TfGoalBroadcaster>(joint_robot_node);
    
    joint_robot->initialize(joint_robot_node, kuka_node, ur10_node);

    // THREADED CALLBACK PROCESSING
    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(kuka_node);
    executor->add_node(ur10_node);
    executor->add_node(joint_robot_node);
    std::thread spin_thread([executor](){ executor->spin(); });

    if(0){
        // ----------------------------------------- iniital position reaching -------------------------------------------------//
        bool reached_q_init = false;
        Eigen::VectorXd q_des(6), q_sing(6);
        q_des << -3.14159, -2.10757, -1.83066, -0.774163, -1.5708, -0.0300288; // example configuration
        q_sing << 0.0, -1.59, 0.0, -1.59, 0.0, 0.0; // singularity configuration
        Eigen::VectorXd q_err = Eigen::VectorXd::Zero(6);
        q_err = q_sing;
        std::cout << q_err.norm() << "\n\n";

        // run joint pose loop (to be used in mission manager)
        joint_robot->reachJointPosition_single(1, q_err, q_sing); // for UR10e robot
        RCLCPP_INFO(rclcpp::get_logger("signal_handler"), "Reached initial joint configuration");

        q_des << 0.0, 0.785398, -1.578, 0.0, 0.785398, 0.0; // example configuration
        q_err = q_des;
        joint_robot->reachJointPosition_single(0, q_err, q_des); // for kuka robot
        RCLCPP_INFO(rclcpp::get_logger("signal_handler"), "Reached initial joint configuration");
        // ----------------------------------------- iniital position reaching -------------------------------------------------//

        // ---------------------------------------------- goal definition ------------------------------------------------------//
        Eigen::VectorXd frm(3);
        frm << 0.0, 0.0, 0.8;
        
        Eigen::VectorXd frame_goal = joint_robot->trasformVector("tool0", "kuka_base_link", frm); 
        Eigen::Affine3d tf_goal = joint_robot->getGenericTransformation("kuka_base_link", "tool0");
        Eigen::Vector3d tool = tf_goal.translation();
        Eigen::Vector3d position(tool(0)+0.5, tool(1), tool(2)); 
        Eigen::Vector3d rpy(0.0, 0.0, 0.0); 
        
        std::string parent_frame = "kuka_base_link"; // or "base_link" for UR10e
        std::string goal_frame  = "ik_reach_goal_2";
        //jointRobot_broadcaster->broadcastStaticTransform(position, rpy, parent_frame, goal_frame);
        // ---------------------------------------------- goal definition ------------------------------------------------------//

        if(0){
            RCLCPP_INFO(joint_robot_node->get_logger(), "\n\n\n [[Starting main loop...]]");
            std::this_thread::sleep_for(2000ms); // 2 sec break before starting
            bool reached_goal = false;
            joint_robot->runCartesianReachingLoop(goal_frame, reached_goal);
        }
    }

    if(0){
        joint_robot->debugJointRobot(1, 0, 0, 0, 0, "kuka_link_6","base_link_inertia");
        //joint_robot->debugJointRobot(0, 0, 0, 0, 0, "base_link_inertia","kuka_link_6");
        //joint_robot->debugKukaRobot(0, 0, 0, 0, 0, " ", " ");
        //joint_robot->debugUR10eRobot(0, 0, 0, 0, 0, " ", " ");
    }

    // closing 
    executor->cancel();
    if(spin_thread.joinable()){
        spin_thread.join();
    }

    rclcpp::shutdown();
    RCLCPP_INFO(kuka_node->get_logger(), "kuka node shut down");
    RCLCPP_INFO(ur10_node->get_logger(), "ur10 node shut down");
    //RCLCPP_INFO(joint_jacobian_publisher->get_logger(), "kuka node shut down");
    return 0;
}