#include "rclcpp/rclcpp.hpp"
#include "uc1_robot_perception/msg/contact.hpp"
#include "uc1_robot_perception/msg/contact_array.hpp"
#include "geometry_msgs/msg/vector3.hpp"

#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include <std_msgs/msg/int32_multi_array.hpp>

#include <vector>
#include <string>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <set>
#include <chrono>

using namespace std::chrono_literals;

class ContactPublisher : public rclcpp::Node
{
public:
  ContactPublisher()
  : Node("contact_publisher")
  {
    multi_pub_ = this->create_publisher<uc1_robot_perception::msg::ContactArray>("contacts", 10);
    marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("contact_control_markers", 10);
    
    key_sub_ = create_subscription<std_msgs::msg::Int32MultiArray>(
      "/keys_pressed", 10,
      std::bind(&ContactPublisher::keysCallback, this, std::placeholders::_1));

    // build a set of simulated contacts
    predefined_contacts_ = {
                createContact({0.0, -0.05, -0.02}, {0.0, -1.0, 0.0}, 2.0, "tool0"),
                createContact({0.01, 0.03, 0.24}, {0.0, 0.0, 1.0}, 3.0, "forearm_link")
                };

  }

  void publishVisualizationMarkers(const uc1_robot_perception::msg::ContactArray & contacts)
  {
    visualization_msgs::msg::MarkerArray marker_array;

    // flushing markers when no keys are pressed 
    if (contacts.contacts.empty()) {
      visualization_msgs::msg::Marker delete_all;
      delete_all.action = visualization_msgs::msg::Marker::DELETEALL;
      marker_array.markers.push_back(delete_all);
      marker_pub_->publish(marker_array);
      return;
    }

    for (size_t i = 0; i < contacts.contacts.size(); ++i) {
      const auto &contact = contacts.contacts[i];

      visualization_msgs::msg::Marker sphere;
      sphere.header.frame_id = contact.reference_frame;
      sphere.header.stamp = now();
      sphere.ns = "contact_sphere";
      sphere.id = static_cast<int>(i);
      sphere.type = visualization_msgs::msg::Marker::SPHERE;
      sphere.action = visualization_msgs::msg::Marker::ADD;
      sphere.pose.position.x = contact.contact_location.x;
      sphere.pose.position.y = contact.contact_location.y;
      sphere.pose.position.z = contact.contact_location.z;
      sphere.pose.orientation.w = 1.0;
      sphere.scale.x = 0.02;
      sphere.scale.y = 0.02;
      sphere.scale.z = 0.02;
      sphere.color.r = 0.0;
      sphere.color.g = 1.0;
      sphere.color.b = 0.0;
      sphere.color.a = 0.6;
      marker_array.markers.push_back(sphere);

      visualization_msgs::msg::Marker arrow;
      arrow.header.frame_id = contact.reference_frame;
      arrow.header.stamp = now();
      arrow.ns = "contact_arrow";
      arrow.id = static_cast<int>(i + 100);
      arrow.type = visualization_msgs::msg::Marker::ARROW;
      arrow.action = visualization_msgs::msg::Marker::ADD;

      geometry_msgs::msg::Point start;
      start.x = contact.contact_location.x;
      start.y = contact.contact_location.y;
      start.z = contact.contact_location.z;
      geometry_msgs::msg::Point end;
      end.x = start.x + contact.contact_normal.x * contact.contact_intensity * 0.1;
      end.y = start.y + contact.contact_normal.y * contact.contact_intensity * 0.1;
      end.z = start.z + contact.contact_normal.z * contact.contact_intensity * 0.1;

      arrow.points = {start, end};
      arrow.scale.x = 0.01;
      arrow.scale.y = 0.02;
      arrow.scale.z = 0.03;
      arrow.color.r = 0.0;
      arrow.color.g = 1.0;
      arrow.color.b = 0.0;
      arrow.color.a = 0.8;

      marker_array.markers.push_back(arrow);
    }

    marker_pub_->publish(marker_array);
  }



private:

  uc1_robot_perception::msg::Contact createContact(
                        const std::array<double,3>& location,
                        const std::array<double,3>& normal,
                        float intensity,
                        const std::string& frame)
  {
    uc1_robot_perception::msg::Contact contact;
    contact.contact_location.x = location[0];
    contact.contact_location.y = location[1];
    contact.contact_location.z = location[2];

    contact.contact_normal.x = normal[0];
    contact.contact_normal.y = normal[1];
    contact.contact_normal.z = normal[2];

    contact.contact_intensity = intensity;
    contact.reference_frame = frame;

    return contact;
  }


  void keysCallback(const std_msgs::msg::Int32MultiArray::SharedPtr msg)
  {
    size_t num_keys_pressed = std::min(msg->data.size(), static_cast<size_t>(2));

    uc1_robot_perception::msg::ContactArray contacts_msg;

    for (size_t i = 0; i < num_keys_pressed; ++i)
    {
      contacts_msg.contacts.push_back(predefined_contacts_[i]);
    }

    // Publish the contacts and their markers
    multi_pub_->publish(contacts_msg);
    publishVisualizationMarkers(contacts_msg);


    RCLCPP_INFO(get_logger(), "Published %zu contact(s) based on %zu pressed key(s).", 
                contacts_msg.contacts.size(), msg->data.size());
  }


  rclcpp::Publisher<uc1_robot_perception::msg::ContactArray>::SharedPtr multi_pub_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
  rclcpp::Subscription<std_msgs::msg::Int32MultiArray>::SharedPtr key_sub_;
  
  std::vector<uc1_robot_perception::msg::Contact> predefined_contacts_;

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ContactPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
