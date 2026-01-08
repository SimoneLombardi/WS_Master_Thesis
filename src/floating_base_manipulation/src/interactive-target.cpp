#include <chrono>
#include <memory>
#include <string>

#include "interactive_markers/interactive_marker_server.hpp"
#include "interactive_markers/menu_handler.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Transform.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Vector3.h"
#include "tf2/transform_datatypes.h"
#include "tf2_ros/transform_broadcaster.h"
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include "visualization_msgs/msg/interactive_marker.hpp"
#include "visualization_msgs/msg/interactive_marker_control.hpp"
#include "visualization_msgs/msg/interactive_marker_feedback.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>

using std::placeholders::_1;

class IkTargetNode : public rclcpp::Node
{
public:
    explicit IkTargetNode(const std::string &node_name, const std::string &frame_name, const rclcpp::NodeOptions &options = rclcpp::NodeOptions());

    ~IkTargetNode() = default;

    inline void
    applyChanges()
    {
        server_->applyChanges();
    }

    visualization_msgs::msg::Marker makeIkMarker(const visualization_msgs::msg::InteractiveMarker &msg);

    visualization_msgs::msg::InteractiveMarkerControl &makeControl(visualization_msgs::msg::InteractiveMarker &msg);

    void make6DofMarker(bool fixed, unsigned int interaction_mode, const tf2::Vector3 &position, const tf2::Quaternion &orientation, bool show_6dof);

    geometry_msgs::msg::TransformStamped getTransform(const std::string& source_frame, const std::string& target_frame);
    void publishTargetTransform(const std::string& marker_frame, const std::string& target_frame);

private:
    void frameCallback();

    void processFeedback(const visualization_msgs::msg::InteractiveMarkerFeedback::ConstSharedPtr &feedback);

    void alignMarker(const visualization_msgs::msg::InteractiveMarkerFeedback::ConstSharedPtr &feedback);

    std::unique_ptr<interactive_markers::InteractiveMarkerServer> server_;
    interactive_markers::MenuHandler menu_handler_;
    std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
    std::shared_ptr<tf2_ros::TransformListener> tf_listener_;
    rclcpp::TimerBase::SharedPtr frame_timer_;
    geometry_msgs::msg::Pose marker_pose_;
    std::string frame_name_;
};

IkTargetNode::IkTargetNode(const std::string &node_name, const std::string &frame_name, const rclcpp::NodeOptions &options)
    : rclcpp::Node(node_name, options), frame_name_(frame_name), menu_handler_()
{
    server_ = std::make_unique<interactive_markers::InteractiveMarkerServer>(
        node_name,
        get_node_base_interface(),
        get_node_clock_interface(),
        get_node_logging_interface(),
        get_node_topics_interface(),
        get_node_services_interface());

    tf_buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
    tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);


    // publish interactive marker tf
    frame_timer_ = create_wall_timer(
        std::chrono::milliseconds(10), std::bind(&IkTargetNode::frameCallback, this));
}

geometry_msgs::msg::TransformStamped IkTargetNode::getTransform(const std::string& source_frame, const std::string& target_frame)
{
    geometry_msgs::msg::TransformStamped transformStamped;

        while (rclcpp::ok())
        {
            try
            {
                transformStamped = tf_buffer_->lookupTransform(source_frame, target_frame, tf2::TimePointZero);
                RCLCPP_INFO(this->get_logger(), "Transform successfully received.");
                break; 
            }
            catch (tf2::TransformException &ex)
            {
                RCLCPP_WARN(this->get_logger(), "Waiting for transform from '%s' to '%s': %s", source_frame.c_str(), target_frame.c_str(), ex.what());
                rclcpp::sleep_for(std::chrono::milliseconds(100));
            }
        }
        
        return transformStamped;
}

visualization_msgs::msg::Marker
IkTargetNode::makeIkMarker(const visualization_msgs::msg::InteractiveMarker &msg)
{
    visualization_msgs::msg::Marker marker;

    marker.type = visualization_msgs::msg::Marker::SPHERE;
    marker.scale.x = msg.scale * 0.05;
    marker.scale.y = msg.scale * 0.05;
    marker.scale.z = msg.scale * 0.05;
    marker.color.r = 1.0;
    marker.color.g = 0.0;
    marker.color.b = 0.0;
    marker.color.a = 0.75;

    return marker;
}

visualization_msgs::msg::InteractiveMarkerControl &IkTargetNode::makeControl(visualization_msgs::msg::InteractiveMarker &msg)
{
    visualization_msgs::msg::InteractiveMarkerControl control;
    control.always_visible = true;
    control.markers.push_back(makeIkMarker(msg));
    msg.controls.push_back(control);

    return msg.controls.back();
}

void IkTargetNode::frameCallback()
{

    tf2::TimePoint tf_time_point(std::chrono::nanoseconds(this->get_clock()->now().nanoseconds()));

    tf2::Stamped<tf2::Transform> transform;
    transform.stamp_ = tf_time_point;
    transform.frame_id_ = "world";
    transform.setOrigin(tf2::Vector3(marker_pose_.position.x, marker_pose_.position.y, marker_pose_.position.z));
    transform.setRotation(tf2::Quaternion(marker_pose_.orientation.x, 
                                            marker_pose_.orientation.y, 
                                            marker_pose_.orientation.z,
                                            marker_pose_.orientation.w));

    geometry_msgs::msg::TransformStamped transform_msg;
    transform_msg = tf2::toMsg(transform);
    transform_msg.child_frame_id = frame_name_;
    tf_broadcaster_->sendTransform(transform_msg);

}

 void IkTargetNode::publishTargetTransform(const std::string& target_frame, const std::string& marker_frame)
    {
        // Create the transform message
        geometry_msgs::msg::TransformStamped transformStamped;
        transformStamped.header.stamp = this->get_clock()->now();
        transformStamped.header.frame_id = target_frame;  
        transformStamped.child_frame_id = marker_frame;
        
        // Set the translation and rotation (coincident with marker frame)
        transformStamped.transform.translation.x = 0.0;
        transformStamped.transform.translation.y = 0.0;
        transformStamped.transform.translation.z = 0.0;
        transformStamped.transform.rotation.x = 0.0;
        transformStamped.transform.rotation.y = 0.0;
        transformStamped.transform.rotation.z = 0.0;
        transformStamped.transform.rotation.w = 1.0;

        // Publish the transform
        tf_broadcaster_->sendTransform(transformStamped);
        RCLCPP_INFO(this->get_logger(), "Published transform from '%s' to '%s'.", marker_frame.c_str(), target_frame.c_str());
    }


void IkTargetNode::processFeedback(
    const visualization_msgs::msg::InteractiveMarkerFeedback::ConstSharedPtr &feedback)
{
    std::ostringstream oss;
    oss << "Feedback from marker '" << feedback->marker_name << "' " << " / control '" << feedback->control_name << "'";

    // store marker pose 
    marker_pose_.position = feedback->pose.position;
    marker_pose_.orientation = feedback->pose.orientation;

    // handle interaction events
    std::ostringstream mouse_point_ss;
    if (feedback->mouse_point_valid)
    {
        mouse_point_ss << " at " << feedback->mouse_point.x << ", " << feedback->mouse_point.y << ", " << feedback->mouse_point.z << " in frame " << feedback->header.frame_id;
    }

    switch (feedback->event_type)
    {
    case visualization_msgs::msg::InteractiveMarkerFeedback::BUTTON_CLICK:
        oss << ": button click" << mouse_point_ss.str() << ".";
        //RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
        break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::MENU_SELECT:
        oss << ": menu item " << feedback->menu_entry_id << " clicked" << mouse_point_ss.str() << ".";
        //RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
        break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::POSE_UPDATE:
        oss << ": pose changed" << "\nposition = " << feedback->pose.position.x << ", " << feedback->pose.position.y << ", " << feedback->pose.position.z << "\norientation = " << feedback->pose.orientation.w << ", " << feedback->pose.orientation.x << ", " << feedback->pose.orientation.y << ", " << feedback->pose.orientation.z << "\nframe: " << feedback->header.frame_id << " time: " << feedback->header.stamp.sec << "sec, " << feedback->header.stamp.nanosec << " nsec";
        //RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
        break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::MOUSE_DOWN:
        oss << ": mouse down" << mouse_point_ss.str() << ".";
        //RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
        break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::MOUSE_UP:
        oss << ": mouse up" << mouse_point_ss.str() << ".";
        //RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
        break;
    }

    server_->applyChanges();
}

void IkTargetNode::alignMarker(
    const visualization_msgs::msg::InteractiveMarkerFeedback::ConstSharedPtr &feedback)
{
    geometry_msgs::msg::Pose pose = feedback->pose;

    pose.position.x = round(pose.position.x - 0.5) + 0.5;
    pose.position.y = round(pose.position.y - 0.5) + 0.5;

    std::ostringstream oss;
    oss << feedback->marker_name << ":" << " aligning position = " << feedback->pose.position.x << ", " << feedback->pose.position.y << ", " << feedback->pose.position.z << " to " << pose.position.x << ", " << pose.position.y << ", " << pose.position.z;
    RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());

    server_->setPose(feedback->marker_name, pose);
    server_->applyChanges();
}

void IkTargetNode::make6DofMarker(
    bool fixed, unsigned int interaction_mode, const tf2::Vector3 &position, const tf2::Quaternion &orientation, bool show_6dof)
{
    visualization_msgs::msg::InteractiveMarker int_marker;
    int_marker.header.frame_id = "world";
    int_marker.pose.position.x = position.getX();
    int_marker.pose.position.y = position.getY();
    int_marker.pose.position.z = position.getZ();
    int_marker.pose.orientation.w = orientation.getW();
    int_marker.pose.orientation.x = orientation.getX();
    int_marker.pose.orientation.y = orientation.getY();
    int_marker.pose.orientation.z = orientation.getZ();
    int_marker.scale = 0.2;

    makeControl(int_marker);
    int_marker.controls[0].interaction_mode = interaction_mode;

    visualization_msgs::msg::InteractiveMarkerControl control;

    if (fixed)
    {
        int_marker.name += "_fixed";
        int_marker.description += "\n(fixed orientation)";
        control.orientation_mode = visualization_msgs::msg::InteractiveMarkerControl::FIXED;
    }

    if (interaction_mode != visualization_msgs::msg::InteractiveMarkerControl::NONE)
    {
        std::string mode_text;
        if (interaction_mode == visualization_msgs::msg::InteractiveMarkerControl::MOVE_3D)
        {
            mode_text = "MOVE_3D";
        }
        else if (interaction_mode == visualization_msgs::msg::InteractiveMarkerControl::ROTATE_3D)
        {
            mode_text = "ROTATE_3D";
        }
        else
        {
            if (interaction_mode == visualization_msgs::msg::InteractiveMarkerControl::MOVE_ROTATE_3D)
            {
                mode_text = "MOVE_ROTATE_3D";
            }
        }
    }

    if (show_6dof)
    {
        tf2::Quaternion orien(1.0, 0.0, 0.0, 1.0);
        orien.normalize();
        control.orientation = tf2::toMsg(orien);
        control.name = "rotate_x";
        control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::ROTATE_AXIS;
        int_marker.controls.push_back(control);
        control.name = "move_x";
        control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::MOVE_AXIS;
        int_marker.controls.push_back(control);

        orien = tf2::Quaternion(0.0, 1.0, 0.0, 1.0);
        orien.normalize();
        control.orientation = tf2::toMsg(orien);
        control.name = "rotate_z";
        control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::ROTATE_AXIS;
        int_marker.controls.push_back(control);
        control.name = "move_z";
        control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::MOVE_AXIS;
        int_marker.controls.push_back(control);

        orien = tf2::Quaternion(0.0, 0.0, 1.0, 1.0);
        orien.normalize();
        control.orientation = tf2::toMsg(orien);
        control.name = "rotate_y";
        control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::ROTATE_AXIS;
        int_marker.controls.push_back(control);
        control.name = "move_y";
        control.interaction_mode = visualization_msgs::msg::InteractiveMarkerControl::MOVE_AXIS;
        int_marker.controls.push_back(control);
    }

    server_->insert(int_marker);
    server_->setCallback(int_marker.name, std::bind(&IkTargetNode::processFeedback, this, _1));
    if (interaction_mode != visualization_msgs::msg::InteractiveMarkerControl::NONE)
    {
        menu_handler_.apply(*server_, int_marker.name);
    }
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    std::string node_name = "floating_base_marker";
    std::string marker_frame_name = "base_float";
    auto node = std::make_shared<IkTargetNode>(node_name, marker_frame_name);

    // initialize base target marker in robot's base frame
    std::string source_frame = marker_frame_name;
    std::string target_frame = "world";
    geometry_msgs::msg::TransformStamped tf_ee;
    tf2::Vector3 position(0, 0, 0);
    tf2::Quaternion orientation(0, 0, 0, 1);

    // initialize base target frame
    node->publishTargetTransform(source_frame, target_frame);

    // run nodes
    node->make6DofMarker(false, visualization_msgs::msg::InteractiveMarkerControl::MOVE_ROTATE_3D, position, orientation, true);
    node->applyChanges();

    // start callback processing
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);
    RCLCPP_INFO(node->get_logger(), "Ready");
    executor.spin();
    rclcpp::shutdown();

    return 0;
}