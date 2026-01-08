#include "rclcpp/rclcpp.hpp"
#include "uc1_robot_perception/msg/contact.hpp"
#include "uc1_robot_perception/msg/contact_array.hpp"
#include "geometry_msgs/msg/vector3.hpp"

using namespace std::chrono_literals;

class ContactPublisher : public rclcpp::Node
{
public:
  ContactPublisher()
  : Node("contact_publisher")
  {
    // Publisher for a single contact message
    single_pub_ = this->create_publisher<uc1_robot_perception::msg::Contact>("contact", 10);
    // Publisher for an array of contact messages
    multi_pub_ = this->create_publisher<uc1_robot_perception::msg::ContactArray>("contacts", 10);
    
    // Timer to publish messages at 1 Hz
    timer_ = this->create_wall_timer(
      1s, std::bind(&ContactPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    // Create and populate a single contact message
    auto contact_msg = uc1_robot_perception::msg::Contact();
    contact_msg.contact_location.x = 1.0;
    contact_msg.contact_location.y = 2.0;
    contact_msg.contact_location.z = 3.0;
    contact_msg.contact_normal.x   = 0.0;
    contact_msg.contact_normal.y   = 0.0;
    contact_msg.contact_normal.z   = 1.0;
    contact_msg.contact_intensity  = 0.8f;
    contact_msg.reference_frame    = "base_link";
    single_pub_->publish(contact_msg);
    RCLCPP_INFO(this->get_logger(), "Published single contact message.");

    // Create a second contact message for the multi-contact scenario
    auto contact2 = uc1_robot_perception::msg::Contact();
    contact2.contact_location.x = 2.0;
    contact2.contact_location.y = 3.0;
    contact2.contact_location.z = 4.0;
    contact2.contact_normal.x   = 0.0;
    contact2.contact_normal.y   = 1.0;
    contact2.contact_normal.z   = 0.0;
    contact2.contact_intensity  = 0.5f;
    contact2.reference_frame    = "end_effector";

    // Create and publish a multi-contact message containing both contacts
    auto array_msg = uc1_robot_perception::msg::ContactArray();
    array_msg.contacts.push_back(contact_msg);
    array_msg.contacts.push_back(contact2);
    multi_pub_->publish(array_msg);
    RCLCPP_INFO(this->get_logger(), "Published multi-contact message.");
  }

  rclcpp::Publisher<uc1_robot_perception::msg::Contact>::SharedPtr single_pub_;
  rclcpp::Publisher<uc1_robot_perception::msg::ContactArray>::SharedPtr multi_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ContactPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
