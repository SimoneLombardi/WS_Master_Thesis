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
static std::string jacobian_to_string(Eigen::MatrixXd matx_1);

class joint_jacobian_publisher_3 : public rclcpp::Node
{
    public:
        joint_jacobian_publisher_3()
        : Node("joint_jacobian_publisher_3"), count_(0)
        {
            publisher_ = this->create_publisher<std_msgs::msg::String>("joint_jacobian_2", 10);

            // initialization call
            timer_ = this->create_wall_timer(500ms, std::bind(&joint_jacobian_publisher_3::timer_callback, this));
        }  
        
        std::shared_ptr<KukaRobot> kuka_robot_ = std::make_shared<KukaRobot>();
        std::shared_ptr<UR10eRobot> ur10_robot_ = std::make_shared<UR10eRobot>();
        
    private:
        std::shared_ptr<rclcpp::Publisher<std_msgs::msg::String>> publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        size_t count_;

        //std::shared_ptr<KukaRobot> kuka_robot_;
        //std::shared_ptr<UR10eRobot> ur10_robot_;

        void timer_callback()
        {   
            auto kukaJ = kuka_robot_->computeJacobian("kuka_link_6");
            auto ur10J = ur10_robot_->computeJacobian("tool0");

            // kuka ur10 transformation
            auto kuka_base_trans_affine = kuka_robot_->getGenericTransformation("kuka_base_link", "kuka_link_6");
            Eigen::MatrixXd kuka_base_rot = kuka_base_trans_affine.rotation();
            //auto ur10_trasf = kuka_base_trans * ur10J;

            // project ur10 jacobian to kuka base frame
            Eigen::MatrixXd jac_projector = Eigen::MatrixXd::Zero(6, 6);
            jac_projector.block(0, 0, 3, 3) = kuka_base_rot; 
            jac_projector.block(3, 3, 3, 3) = kuka_base_rot;

            // concatenate jacobians
            Eigen::MatrixXd joint_jacobian(6, 12);
            joint_jacobian.block(0, 0, 6, 6) = kukaJ;                           // first 6 columns-> kuka jacobian
            joint_jacobian.block(0, 6, 6, 6) = jac_projector * ur10J;           // last 6 columns -> ur10 jacobian projected to kuka base frame    

            //std::cout << "UR Jacobian size\n " << ur10J.size() << std::endl;
            //std::cout << "KUKA Jacobian size\n " << kukaJ.size() << std::endl;
            //std::cout << "base transform:\n " << kuka_base_rot << std::endl;
            //std::cout << "Joint Jacobian:\n " << joint_jacobian << std::endl;

            //std::cout << "kuka projector\n " << jac_projector << std::endl;

            auto message = std_msgs::msg::String();
            //message.data = std::to_string(count_++);
            message.data = jacobian_to_string(joint_jacobian);
            RCLCPP_INFO(this->get_logger(), "Pub: '%s'", message.data.c_str());
            publisher_->publish(message);
        }
        
};


int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto joint_jacobian_publisher = std::make_shared<joint_jacobian_publisher_3>();
    
    auto kuka_node = std::make_shared<rclcpp::Node>("kuka_robot_node");
    auto ur10_node = std::make_shared<rclcpp::Node>("ur10_robot_node");

    auto kuka_broadcaster = std::make_shared<TfGoalBroadcaster>(kuka_node);
    auto ur10_broadcaster = std::make_shared<TfGoalBroadcaster>(ur10_node);

    joint_jacobian_publisher->kuka_robot_->initialize(kuka_node);
    joint_jacobian_publisher->ur10_robot_->initialize(ur10_node);

    // THREADED CALLBACK PROCESSING
    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(kuka_node);
    executor->add_node(ur10_node);
    executor->add_node(joint_jacobian_publisher);
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

static std::string jacobian_to_string(Eigen::MatrixXd matx_1)
{
    std::stringstream ss;
    ss << matx_1;
    return ss.str();
}


