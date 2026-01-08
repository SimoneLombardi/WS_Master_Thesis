#include "rclcpp/rclcpp.hpp"
#include "KukaRobot.hpp"
#include "TfGoalBroadcaster.hpp"
#include <csignal>

bool loop = true;

void signal_handler(int signum)
{
    loop = false;
    RCLCPP_INFO(rclcpp::get_logger("signal_handler"), "Shutdown signal received. Exiting...");
}

using namespace std::chrono_literals;

// TODO Issue with joint state publisher: I cannot overwrite the values from the main one (the robot tries to always go back in place)
// but I cannot launch the display without it, otherwise I don't get any tf and the model will crash (chicken-egg)
// Need to find a workaround
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    auto kuka_node = std::make_shared<rclcpp::Node>("kuka_robot_node");
    auto kuka_robot = std::make_shared<KukaRobot>();

    auto broadcaster_node = std::make_shared<TfGoalBroadcaster>(kuka_node);

    kuka_robot->initialize(kuka_node);

    // threaded callback processing
    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(kuka_node);
    std::thread spin_thread([executor](){ executor->spin(); });

    // joint target configuration
    Eigen::VectorXd qdot_des = Eigen::VectorXd::Zero(6);
    Eigen::VectorXd q_des(6);
    auto q_init = kuka_robot->getJointPositions();
    std::cout << q_init << "\n\n";
    
    q_des = q_init;
    //q_des(0) = q_des(0) - 1.57;  // for joint limit testing
    q_des(1) = q_des(1) - 1.57;
    q_des(2) = q_des(2) + 1.57;

    RCLCPP_INFO(rclcpp::get_logger("signal_handler"), "KUKA Robot Configured");

    bool reached_q_init = false;
    Eigen::VectorXd q_err = Eigen::VectorXd::Zero(6);
    q_err = q_des;
    std::cout << q_err.norm() << "\n\n";

    int loop_rate_hz;

    // run joint pose loop (to be used in mission manager)
    kuka_robot->runJointControlLoop(q_err, q_des);
    RCLCPP_INFO(rclcpp::get_logger("signal_handler"), "Reached initial joint configuration");

    // ----------------------------------------- cartesian control loop

    // publish test goal 
    Eigen::Vector3d position(2.5, 0.8, 1.25);
    Eigen::Vector3d rpy(0.0, 0.707, 1.57);
    std::string parent_frame = "kuka_base_link";
    std::string goal_frame  = "ik_tool_frame_kuka";
    broadcaster_node->broadcastStaticTransform(position, rpy, parent_frame, goal_frame);

    RCLCPP_INFO(kuka_node->get_logger(), "Starting main loop...");
    std::this_thread::sleep_for(2000ms); // 2 sec break before starting
    bool reached_goal = false;
    kuka_robot->runCartesianReachingLoop(goal_frame, reached_goal);

    // free background execution resources
    executor->cancel();
    if (spin_thread.joinable())
    {
        spin_thread.join();
    }

    rclcpp::shutdown();
    RCLCPP_INFO(kuka_node->get_logger(), "Kuka node shut down successfully.");

    return 0;
}
