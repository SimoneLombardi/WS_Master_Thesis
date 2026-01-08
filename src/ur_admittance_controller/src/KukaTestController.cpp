#include "rclcpp/rclcpp.hpp"
#include "KukaRobot.hpp"
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

    kuka_robot->initialize(kuka_node);

    // threaded callback processing
    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(kuka_node);
    std::thread spin_thread([executor]()
                            { executor->spin(); });

    // basic joint control test
    Eigen::VectorXd qdot_des = Eigen::VectorXd::Zero(6);
    Eigen::VectorXd q_des(6);
    auto q_init = kuka_robot->getJointPositions();
    q_des = q_init;
    q_des(0) = q_des(0) + 0.7;
    q_des(1) = q_des(1) - 1.57;
    q_des(2) = q_des(2) + 1.57;
    float Kp = 0.005;

    // ----------------------------------------- interface testing loop
    rclcpp::Rate loop_rate(100); // testing rates
    RCLCPP_INFO(kuka_node->get_logger(), "Starting main loop...");
    std::this_thread::sleep_for(2000ms);
    for (int i=0; i < 1000; i++)
    {
            // check tf 
            auto transformations = kuka_robot->getTransformations();
            for (const auto &tf : transformations)
            {
                Eigen::Vector3d translation = tf.translation();
                //std::cout << "Translation: [ " << translation.x() << ", " << translation.y() << ", " << translation.z() << " ]" << std::endl;
            }

            // check joint readings
            auto q = kuka_robot->getJointPositions();

            // check joint control
            // for (int j=0; j < qdot_des.size(); j++)
            // {
            //     qdot_des(j) = Kp*(q_des(j) - q(j));
            // }
            // std::cout << qdot_des << std::endl;
            // kuka_robot->updateJointPositionCommand(q, qdot_des);

            // compute cartesian reaching task (tool)
            Eigen::Affine3d goal_tf = kuka_robot->getGenericTransformation("kuka_base_link", "ik_reach_goal");
            Eigen::VectorXd cart_err(6);
            cart_err = kuka_robot->computeCartesianReachingTask(goal_tf, transformations.back()); 
            //std::cout << cart_err << std::endl;

            // compute reaching ik control (tool)
            auto J = kuka_robot->computeJacobian("kuka_link_6");
            auto Jpinv = kuka_robot->computePseudoInverse(J);
            Eigen::VectorXd qdot_des = Kp * (Jpinv * cart_err);

            // skip first iterations and send command
            if (i > 5) kuka_robot->updateJointPositionCommand(q, qdot_des);

            RCLCPP_INFO(kuka_node->get_logger(), "Main loop running");
            loop_rate.sleep();
    }

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
