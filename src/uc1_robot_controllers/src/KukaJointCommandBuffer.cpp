#include <memory>
#include <vector>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

using std::placeholders::_1;

class JointStateHandler : public rclcpp::Node
{
public:
  JointStateHandler() : Node("joint_state_handler")
  {
    // Initialize the class member vector with zeros (size 6)
    joint_state_.resize(6, 0.0);

    // add crf demo initial config
    joint_state_[1] = -2.10;
    joint_state_[2] = 2.40;
    joint_state_[4] = -1.57;

    // Create a publisher on the /joint_state_publisher topic
    publisher_ = this->create_publisher<sensor_msgs::msg::JointState>(
      "/joint_states", 10
    );

    // Create a subscriber to a topic that provides 6 doubles (e.g. /joint_state_input)
    subscription_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/kuka_joint_state_buffer", 10,
      std::bind(&JointStateHandler::topic_callback, this, _1)
    );

    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(10),
      std::bind(&JointStateHandler::publish_joint_state, this)
    );
  }

private:
  void topic_callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg)
  {
    // Store only the first 6 elements if available
    if (msg->data.size() >= 6) {
      for (size_t i = 0; i < 6; ++i) {
        joint_state_[i] = msg->data[i];
      }
    } else {
      RCLCPP_WARN(this->get_logger(), "Received array with fewer than 6 elements.");
    }

    //publish at the end of callback to keep everythinc synced
    //publish_joint_state();
  }

  void publish_joint_state()
  {
    auto joint_state_msg = sensor_msgs::msg::JointState();
    joint_state_msg.header.stamp = this->get_clock()->now();
    joint_state_msg.header.frame_id = "kuka_base_link";
    joint_state_msg.name = ordered_joint_names_;
    joint_state_msg.position = {joint_state_[0], 
                                 joint_state_[1],
                                 joint_state_[2],
                                 joint_state_[3],
                                 joint_state_[4],
                                 joint_state_[5]};

    // Publish on the /joint_state_publisher topic
    publisher_->publish(joint_state_msg);
  }

  // Member variables
  std::vector<double> joint_state_;  // stores the current joint state of size 6
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr publisher_;
  std::vector<std::string> ordered_joint_names_ = {"kuka_joint_a1", "kuka_joint_a2", "kuka_joint_a3", "kuka_joint_a4", "kuka_joint_a5", "kuka_joint_a6"};
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<JointStateHandler>());
  rclcpp::shutdown();
  return 0;
}
