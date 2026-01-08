#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/buffer.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"
#include "tf2_ros/static_transform_broadcaster.h"

class TfPublisherNode : public rclcpp::Node
{
public:
    TfPublisherNode() : Node("tf_publisher_node")
    {
        tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
        static_tf_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10),
            std::bind(&TfPublisherNode::publishTargetTransform, this));
    }

private:
    void publishTargetTransform()
    {
        std::string source_frame = "base_link"; 
        std::string target_frame = "tool0";    
        std::string new_target_frame = "ik_target_ee"; 

        geometry_msgs::msg::TransformStamped transformStamped;

        try
        {
            transformStamped = tf_buffer_->lookupTransform(source_frame, target_frame, tf2::TimePointZero);
            RCLCPP_INFO(this->get_logger(), "Transform from '%s' to '%s' received.", source_frame.c_str(), target_frame.c_str());

            // Define the new target frame 'ik_target_ee' relative to 'base'
            geometry_msgs::msg::TransformStamped goal_transform;
            goal_transform.header.stamp = this->get_clock()->now();
            goal_transform.header.frame_id = source_frame; // Parent frame (base)
            goal_transform.child_frame_id = new_target_frame; // Child frame (ik_target_ee)

            // match the tool0 transform + offset
            goal_transform.transform.translation = transformStamped.transform.translation;
            goal_transform.transform.rotation = transformStamped.transform.rotation;
            //goal_transform.transform.translation.x += 0.1;

            // Publish the new transform
            static_tf_broadcaster_->sendTransform(goal_transform);
            RCLCPP_INFO(this->get_logger(), "Published transform from '%s' to '%s'.", source_frame.c_str(), new_target_frame.c_str());

            // unsubscribe callback to stop publishing
            timer_->cancel();
        }
        catch (tf2::TransformException &ex)
        {
            RCLCPP_WARN(this->get_logger(), "Could not get transform from '%s' to '%s': %s", source_frame.c_str(), target_frame.c_str(), ex.what());
        }
    }

    // ROS2 components for TF2
    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> static_tf_broadcaster_;
    rclcpp::TimerBase::SharedPtr timer_; 
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    // Create a node and an executor
    auto node = std::make_shared<TfPublisherNode>();
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
