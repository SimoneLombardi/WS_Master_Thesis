
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
#include "visualization_msgs/msg/interactive_marker.hpp"
#include "visualization_msgs/msg/interactive_marker_control.hpp"
#include "visualization_msgs/msg/interactive_marker_feedback.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>  

#define LINK_ZERO_NAME "kuka_base_link" // nome del primo link del quale devo calcolare le proximity task

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

    // parameter 
    std::vector<double> position_;
    std::vector<double> orientation_;

private:
    void frameCallback();

    void processFeedback(const visualization_msgs::msg::InteractiveMarkerFeedback::ConstSharedPtr &feedback);

    void alignMarker(const visualization_msgs::msg::InteractiveMarkerFeedback::ConstSharedPtr &feedback);

    std::unique_ptr<interactive_markers::InteractiveMarkerServer> server_;
    interactive_markers::MenuHandler menu_handler_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
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

    // publish interactive marker tf
    frame_timer_ = create_wall_timer(
        std::chrono::milliseconds(10), std::bind(&IkTargetNode::frameCallback, this));

    // pos ori parameter
    position_ = declare_parameter<std::vector<double>>("position", {0.0, 0.0, 0.0});
    orientation_ = declare_parameter<std::vector<double>>("orientation", {0.0, 0.0, 0.0});
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

visualization_msgs::msg::InteractiveMarkerControl &
IkTargetNode::makeControl(visualization_msgs::msg::InteractiveMarker &msg)
{
    visualization_msgs::msg::InteractiveMarkerControl control;
    control.always_visible = true;
    control.markers.push_back(makeIkMarker(msg));
    msg.controls.push_back(control);

    return msg.controls.back();
}

void IkTargetNode::frameCallback()
{

    if (!tf_broadcaster_)
    {
        tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(shared_from_this());
    }

    tf2::TimePoint tf_time_point(std::chrono::nanoseconds(this->get_clock()->now().nanoseconds()));

    tf2::Stamped<tf2::Transform> transform;
    transform.stamp_ = tf_time_point;
    transform.frame_id_ = LINK_ZERO_NAME;
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
        RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
        break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::MENU_SELECT:
        oss << ": menu item " << feedback->menu_entry_id << " clicked" << mouse_point_ss.str() << ".";
        RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
        break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::POSE_UPDATE:
        oss << ": pose changed" << "\nposition = " << feedback->pose.position.x << ", " << feedback->pose.position.y << ", " << feedback->pose.position.z << "\norientation = " << feedback->pose.orientation.w << ", " << feedback->pose.orientation.x << ", " << feedback->pose.orientation.y << ", " << feedback->pose.orientation.z << "\nframe: " << feedback->header.frame_id << " time: " << feedback->header.stamp.sec << "sec, " << feedback->header.stamp.nanosec << " nsec";
        RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
        break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::MOUSE_DOWN:
        oss << ": mouse down" << mouse_point_ss.str() << ".";
        RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
        break;

    case visualization_msgs::msg::InteractiveMarkerFeedback::MOUSE_UP:
        oss << ": mouse up" << mouse_point_ss.str() << ".";
        RCLCPP_INFO(get_logger(), "%s", oss.str().c_str());
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
    int_marker.header.frame_id = LINK_ZERO_NAME;
    int_marker.pose.position.x = position.getX();
    int_marker.pose.position.y = position.getY();
    int_marker.pose.position.z = position.getZ();
    int_marker.pose.orientation.w = orientation.getW();
    int_marker.pose.orientation.x = orientation.getX();
    int_marker.pose.orientation.y = orientation.getY();
    int_marker.pose.orientation.z = orientation.getZ();
    int_marker.scale = 0.5;

    // insert a box
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

    // std::string node_name1 = "ik_target_ee_marker";
    // std::string frame_name1 = "ik_target_ee";
    std::string node_name2 = "ik_target_body_marker";
    std::string frame_name2 = "ik_target_body";

    // create two nodes with different names and frame names
    //auto node1 = std::make_shared<IkTargetNode>(node_name1, frame_name1);
    auto node2 = std::make_shared<IkTargetNode>(node_name2, frame_name2);

    // hard-coded initial positions for the markers, change as necessary
    //tf2::Vector3 position1(-0.077, 0.257, 0.899);
    //tf2::Quaternion orientation1;
    //orientation1.setRPY(1.897, -0.277, -2.234);

    // get the parameters
    if(node2->has_parameter("position")){
        RCLCPP_INFO(node2->get_logger(), "\n%f %f %f", node2->position_[0], node2->position_[1], node2->position_[2]);
    }else{
        RCLCPP_WARN(node2->get_logger(), "Missing parameter, position");
    }

    if(node2->has_parameter("orientation")){
        RCLCPP_INFO(node2->get_logger(), "%f %f %f\n", node2->orientation_[0], node2->orientation_[1], node2->orientation_[2]);
    }else{
        RCLCPP_WARN(node2->get_logger(), "Missing parameter, orientation");
    }

    tf2::Vector3 position2(node2->position_[0], 
                           node2->position_[1], 
                           node2->position_[2]);
    tf2::Quaternion orientation2;
    orientation2.setRPY(node2->orientation_[0], 
                        node2->orientation_[1], 
                        node2->orientation_[2]);

    // run nodes
    //node1->make6DofMarker(false, visualization_msgs::msg::InteractiveMarkerControl::MOVE_ROTATE_3D, position1, orientation1, true);
    //node1->applyChanges();

    node2->make6DofMarker(false, visualization_msgs::msg::InteractiveMarkerControl::MOVE_ROTATE_3D, position2, orientation2, true);
    node2->applyChanges();

    // start callback processing
    rclcpp::executors::SingleThreadedExecutor executor;
    //executor.add_node(node1);
    executor.add_node(node2);
    //RCLCPP_INFO(node2->get_logger(), "Ready");
    executor.spin();
    rclcpp::shutdown();

    return 0;
}