#include "rclcpp/rclcpp.hpp"
#include "UR10eRobot.hpp"
#include <csignal>
#include <cmath>

bool loop = true;

void signal_handler(int signum)
{
    loop = false;
    RCLCPP_INFO(rclcpp::get_logger("signal_handler"), "Shutdown signal received. Exiting...");
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    auto ur10e_node = std::make_shared<rclcpp::Node>("ur10e_robot_node");
    auto ur10e_robot = std::make_shared<UR10eRobot>();

    ur10e_robot->initialize(ur10e_node);

    // threaded callback processing
    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(ur10e_node);
    std::thread spin_thread([executor]()
                            { executor->spin(); });

    rclcpp::Rate loop_rate(100); // 100 Hz

    // ----------------------------------------- initial configuration reaching

    bool reached_q_init = false;
    Eigen::VectorXd q_des(6);
    q_des << -3.14159, -2.10757, -1.83066, -0.774163, -1.5708, -0.0300288;
    Eigen::VectorXd q_err = Eigen::VectorXd::Zero(6);
    q_err = q_des;
    std::cout << q_err.norm() << "\n\n";
    /*
    while (rclcpp::ok() && q_err.norm() > 0.01)
    {
            // check joint state
            auto q = ur10e_robot->getJointPositions();

            // send joint command 
            float kp = 0.2;
            Eigen::MatrixXd Kp = Eigen::MatrixXd::Identity(6,6);
            Kp = kp * Kp;
            
            Eigen::VectorXd qdot_des = Eigen::VectorXd::Zero(6);

            // proportional joint controller
            q_err = q_des - q;
            qdot_des = Kp * q_err;

            // skip first iterations and send command
            //if (q.norm() != 0) ur10e_robot->sendJointVelocityCommand(qdot_des);
            
            loop_rate.sleep();
    }
    */
    RCLCPP_INFO(rclcpp::get_logger("signal_handler"), "Reached initial joint configuration");

    // ----------------------------------------- admittance control loop
    ur10e_robot->zeroFtSensor();

    // lowpass params
    double alpha = 0.9;         // Tuning parameter
    Eigen::VectorXd prev_filtered_w = Eigen::VectorXd::Zero(6); // Holds y[k-1] in discrete steps

    int stop_count = 0;
    while (rclcpp::ok())
    {

            // get force/torque readings
            auto w = ur10e_robot->getWristWrench();

            // raw wrench filtering
            Eigen::VectorXd filtered_w = alpha * prev_filtered_w + (1.0 - alpha) * w;  
            prev_filtered_w = filtered_w;

            // debug 
            ur10e_robot->publishFilteredWrench(filtered_w);
            //std::cout << w << "\n\n";

            // admittance activation
            double linear_w_norm = filtered_w.head(3).norm();
            double admittance_gain = 1/(1 + exp(-2.5*(linear_w_norm - 5)));

            // check robot state
            auto transformations = ur10e_robot->getTransformations();
            for (const auto &tf : transformations)
            {
                Eigen::Vector3d translation = tf.translation();
                //std::cout << "Translation: [ " << translation.x() << ", " << translation.y() << ", " << translation.z() << " ]" << std::endl;
            }

            // check joint state
            auto q = ur10e_robot->getJointPositions();

            // admittance control law (need to tune admittance gains)
            Eigen::VectorXd admittance = Eigen::VectorXd::Zero(6); 
            admittance(0) = filtered_w(1); 
            admittance(1) = filtered_w(0); 
            admittance(2) = -filtered_w(2); 

            float Kp = 0.01;
            auto J = ur10e_robot->computeJacobian("tool0");
            auto Jpinv = ur10e_robot->computePseudoInverse(J);
            Eigen::VectorXd qdot_des = Kp * admittance_gain * (Jpinv * admittance);

            std::cout << qdot_des << "\n\n";

            // compute reaching ik control (shoulder, for basic avoidance)
            // auto J = ur10e_robot->computeJacobian("forearm_link");
            // auto Jpinv = ur10e_robot->computePseudoInverse(J);
            // Eigen::VectorXd qdot_des(6);
            // qdot_des << 0, 0, 0, 0, 0, 0;
            // qdot_des.head(3) = Kp * (Jpinv * cart_err);

            if (stop_count > 50000)
            {
                rclcpp::shutdown();
                exit(0);
            }

            // skip first iterations and send command
            ur10e_robot->sendJointVelocityCommand(qdot_des);
            stop_count++;
            loop_rate.sleep();
    }

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
