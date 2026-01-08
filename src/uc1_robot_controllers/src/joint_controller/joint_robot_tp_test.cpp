#include "TfGoalBroadcaster.hpp"
#include "JointRobotTP.hpp"
#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"

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
    auto joint_robot_tp = std::make_shared<JointRobotTP>();
    auto joint_robot_node = std::make_shared<rclcpp::Node>("joint_robot_tp_node");
    
    auto kuka_node = std::make_shared<rclcpp::Node>("kuka_robot_node");
    auto ur10_node = std::make_shared<rclcpp::Node>("ur10_robot_node");

    joint_robot_tp->initialize(joint_robot_node, kuka_node, ur10_node);

    // THREADED CALLBACK PROCESSING
    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(kuka_node);
    executor->add_node(ur10_node);
    executor->add_node(joint_robot_node);
    std::thread spin_thread([executor](){ executor->spin(); });

    // closing 
    executor->cancel();
    if(spin_thread.joinable()){
        spin_thread.join();
    }

    rclcpp::shutdown();
    RCLCPP_INFO(rclcpp::get_logger("joint_robot_tp_test"), "Joint Robot TP Test finished.");
    return 0;
}