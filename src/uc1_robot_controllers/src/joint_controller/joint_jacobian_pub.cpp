#include "KukaRobot.hpp"
#include "UR10eRobot.hpp"
#include "RobotInterface.hpp"
#include "TfGoalBroadcaster.hpp"

#include <csignal>
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

/*
    Come prima task voglio creare un pusblisher che pubblica la jacobiana dei due robot come uno intero
*/

class joint_jacobian_publisher : public rclcpp:: Node
{
    public:
        joint_jacobian_publisher()
        : Node("joint_jacobian_publisher"), count_(0)
        {
            publisher_ = this->create_publisher<std_msgs::msg::String>("joint_jacobian", 10);
            timer_ = this->create_wall_timer(
            500ms, std::bind(&joint_jacobian_publisher::timer_callback, this));
        }

    private:
        void init_robot_kuka()
        {
            // ROBOT INITIALIZATION
            auto kuka_node_ = std::make_shared<rclcpp::Node>("kuka_robot_node");
            auto kuka_robot_ = std::make_shared<KukaRobot>();

            // robot broadcaster node creation
            //auto kuka_broadcaster_node = std::make_shared<TfGoalBroadcaster>(kuka_node_);
            

            kuka_robot_->initialize(kuka_node_);
        }

        /*void init_robot_ur10()
        {
            // ROBOT INITIALIZATION
            auto ur10_node = std::make_shared<rclcpp::Node>("ur10_robot_node");
            auto ur10_robot = std::make_shared<UR10eRobot>();

            // robot broadcaster node creation
            auto ur10_broadcaster_node = std::make_shared<TfGoalBroadcaster>(ur10_node);

            kuka_robot->initialize(kuka_node);
            ur10_robot->initialize(ur10_node);
        }*/

        void timer_callback()
        {
            auto message = std_msgs::msg::String();
            message.data = "Hello, world! " + std::to_string(count_++);
            RCLCPP_INFO(this->get_logger(), ".");
            publisher_->publish(message);
        }
        rclcpp::TimerBase::SharedPtr timer_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        size_t count_;

        KukaRobot kuka_robot_;
        rclcpp::Node kuka_node_;
        //UR10eRobot ur10_robot_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    // PUBLISHER INITIALIZATION
    auto pub_node = std::make_shared<joint_jacobian_publisher>();

    // THREADED CALLBACK PROCESSING
    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    //executor->add_node(kuka_node);
    //executor->add_node(ur10_node);
    executor->add_node(pub_node);
    std::thread spin_thread([executor](){ executor->spin(); });

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