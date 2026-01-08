#include <memory>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/msg/transform_stamped.hpp>

using namespace std::chrono_literals;

class TfPublisherNode : public rclcpp::Node
{
public:
    TfPublisherNode()
        : Node("tf_publisher_node")
    {
        // Create a timer that will call the publishTF method every 100ms
        timer_ = this->create_wall_timer(10ms, std::bind(&TfPublisherNode::publishTF, this));
        tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
    }

private:
    void publishTF()
    {
        // Create a TransformStamped message
        geometry_msgs::msg::TransformStamped transform_stamped;

        // Fill in the message
        transform_stamped.header.stamp = this->get_clock()->now();
        transform_stamped.header.frame_id = "forearm_link";
        transform_stamped.child_frame_id = "mindist_point_frame";

        // Set the translation (position)
        transform_stamped.transform.translation.x = -0.30;
        transform_stamped.transform.translation.y = 0.0;
        transform_stamped.transform.translation.z = 0.02;

        // Set the rotation (orientation) - here we use a unit quaternion (no rotation)
        tf2::Quaternion q;
        q.setRPY(0.0, 0.0, 0.0); // Roll, Pitch, Yaw
        transform_stamped.transform.rotation.x = q.x();
        transform_stamped.transform.rotation.y = q.y();
        transform_stamped.transform.rotation.z = q.z();
        transform_stamped.transform.rotation.w = q.w();

        // Publish the transform
        tf_broadcaster_->sendTransform(transform_stamped);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TfPublisherNode>());
    rclcpp::shutdown();
    return 0;
}
