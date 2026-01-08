#include "rclcpp/rclcpp.hpp"
#include "UR10eRobot.hpp"
#include "TfGoalBroadcaster.hpp"
#include <csignal>



bool loop = true;

void signal_handler(int signum)
{
    loop = false;
    RCLCPP_INFO(rclcpp::get_logger("signal_handler"), "Shutdown signal received. Exiting...");
}

using namespace std::chrono_literals;

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    auto ur10e_node = std::make_shared<rclcpp::Node>("ur10e_robot_node");
    auto ur10e_robot = std::make_shared<UR10eRobot>();

    auto broadcaster_node = std::make_shared<TfGoalBroadcaster>(ur10e_node);

    ur10e_robot->initialize(ur10e_node);

    // threaded callback processing
    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(ur10e_node);
    std::thread spin_thread([executor]() { executor->spin(); });

    // ----------------------------------------- initial configuration reaching
    bool reached_q_init = false;
    Eigen::VectorXd q_des(6);
    q_des << -3.14159, -3.10757, -0.83066, -0.774163, -1.5708, -0.0300288;
    Eigen::VectorXd q_err = Eigen::VectorXd::Zero(6);
    q_err = q_des;
    std::cout << q_err.norm() << "\n\n";
    // run joint pose loop (to be used in mission manager)
    ur10e_robot->runJointControlLoop(q_err, q_des);
    RCLCPP_INFO(rclcpp::get_logger("signal_handler"), "Reached initial joint configuration");

    // ----------------------------------------- cartesian controller
    // publish test goal 
    Eigen::Vector3d position(0.7, 0.0, 0.5);
    Eigen::Vector3d rpy(0.0, 0.0, 0.0);
    std::string parent_frame = "base_link";
    std::string goal_frame  = "ik_reach_goal";
    broadcaster_node->broadcastStaticTransform(position, rpy, parent_frame, goal_frame);

    //RCLCPP_INFO(ur10e_node->get_logger(), "Starting main loop...");
    //std::this_thread::sleep_for(2000ms); // 2 sec break before starting
    //bool reached_goal = false;
    //ur10e_robot->runCartesianReachingLoop(goal_frame, reached_goal);

    RCLCPP_INFO(ur10e_node->get_logger(), "Starting proximity avoidance loop...");
    std::this_thread::sleep_for(2000ms); // 2 sec break before starting
    bool reached_goal = false;
    ur10e_robot->runProximityControlLoop(goal_frame, reached_goal);

    // free background execution resources
    executor->cancel();
    if (spin_thread.joinable())
    {
        spin_thread.join();
    }

    rclcpp::shutdown();
    RCLCPP_INFO(ur10e_node->get_logger(), "UR10e node shut down successfully.");

    return 0;
}
