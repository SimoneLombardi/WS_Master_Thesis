#include "rclcpp/rclcpp.hpp"
#include "UR10eRobot.hpp"
#include <csignal>

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


    // instance of proximity sensory network
    auto ProxyNet = ur10e_robot->getProximityNetwork();

    // ----------------------------------------- interface testing loop
    rclcpp::Rate loop_rate(100); // 100 Hz
    int stop_count = 0;
    while (rclcpp::ok())
    {
            // update proximity data
            auto raw_tof_distances = ProxyNet->getShmRawData();

            // get pointclouds from raw tof data
            std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> tof_clouds;
            for (int i=0; i < ProxyNet->getActiveTofNumber(); i++)
            {
                pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_tmp(new pcl::PointCloud<pcl::PointXYZ>);
                ProxyNet->buildPointCloudfromShm(raw_tof_distances[i], cloud_tmp);
                tof_clouds.push_back(cloud_tmp);
            }

            // merge tof clouds
            pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_full(new pcl::PointCloud<pcl::PointXYZ>);

            // broadcast point cloud (not necessary for control, no need for ros2)

            // check robot state
            auto transformations = ur10e_robot->getTransformations();
            for (const auto &tf : transformations)
            {
                Eigen::Vector3d translation = tf.translation();
                //std::cout << "Translation: [ " << translation.x() << ", " << translation.y() << ", " << translation.z() << " ]" << std::endl;
            }

            // check joint state
            auto q = ur10e_robot->getJointPositions();

            // send joint command 
            // float Kp = 0.1;
            // Eigen::VectorXd qdot_des = Eigen::VectorXd::Zero(6);
            // Eigen::VectorXd q_des(6);
            // q_des << 1.57, 0, 0, 0, 0, 0;
            // for (int j=0; j < qdot_des.size(); j++)
            // {
            //     qdot_des(j) = Kp*(q_des(j) - q(j));
            // }
            // ur10e_robot->sendJointVelocityCommand(qdot_des);

            // compute cartesian reaching task (tool)
            Eigen::Affine3d goal_tf = ur10e_robot->getGenericTransformation("base_link", "ik_reach_goal");
            Eigen::VectorXd cart_err(6);
            cart_err = ur10e_robot->computeCartesianReachingTask(goal_tf, transformations.back()); // goal and tool frames

            //Eigen::Affine3d goal_tf = ur10e_robot->getGenericTransformation("base_link", "forearm_reach_goal");
            //Eigen::VectorXd cart_err(6);
            //cart_err = ur10e_robot->computeCartesianReachingTask(goal_tf, transformations[3]); // goal and tool frames
            //cart_err.tail(3) = Eigen::Vector3d::Zero();
            
            // compute reaching ik control (tool)
            float Kp = 0.5;
            auto J = ur10e_robot->computeJacobian("tool0");
            auto Jpinv = ur10e_robot->computePseudoInverse(J);
            Eigen::VectorXd qdot_des = Kp * (Jpinv * cart_err);

            // compute reaching ik control (shoulder, for basic avoidance)
            // auto J = ur10e_robot->computeJacobian("forearm_link");
            // auto Jpinv = ur10e_robot->computePseudoInverse(J);
            // Eigen::VectorXd qdot_des(6);
            // qdot_des << 0, 0, 0, 0, 0, 0;
            // qdot_des.head(3) = Kp * (Jpinv * cart_err);
            // std::cout << qdot_des << std::endl;

            if (stop_count > 2)
            {
                rclcpp::shutdown();
                exit(0);
            }

            // skip first iterations and send command
            //if (i > 5) ur10e_robot->sendJointVelocityCommand(qdot_des);
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
