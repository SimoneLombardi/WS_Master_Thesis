#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <pcl/common/transforms.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2_eigen/tf2_eigen.h>
#include <cmath>

#define LINK_ZERO_NAME "kuka_base_link" // nome del primo link del quale devo calcolare le proximity task

class CylinderPointCloudPublisher : public rclcpp::Node
{
public:
  CylinderPointCloudPublisher() : Node("cylinder_pointcloud_publisher"),
    tf_buffer_(this->get_clock()),
    tf_listener_(tf_buffer_)
  {
    publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/environment_point_cloud", 10);
    timer_ = this->create_wall_timer(
      std::chrono::milliseconds(50),
      std::bind(&CylinderPointCloudPublisher::timer_callback, this)
    );
  }

private:
  void timer_callback()
  {
    // build sphere cloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    cloud->header.frame_id = "ik_target_body";

    double radius = 0.1; // 10 cm
    double height = 1.5; // 150 cm
    int num_theta = 20;  // polar angle steps
    int num_steps_height = 30; // height steps
    //int num_phi = 20;    // azimuth angle steps

    //generate cylinder
    for(int i=0; i<=num_theta; ++i){
        double theta = 2.0 * M_PI * i / num_theta;
        for(int j=0; j<=num_steps_height; ++j){
            if(i%2==0 && j%2==0){
              double z = (height / num_steps_height) * j;
              pcl::PointXYZ point;
              point.x = radius * std::cos(theta);
              point.y = radius * std::sin(theta);
              point.z = z;
              cloud->points.push_back(point);
            }else if(i%2==1 && j%2==1){
              double z = (height / num_steps_height) * j;
              pcl::PointXYZ point;
              point.x = radius * std::cos(theta);
              point.y = radius * std::sin(theta);
              point.z = z;
              cloud->points.push_back(point);
            }
        }
    }
    
    cloud->width = static_cast<uint32_t>(cloud->points.size());
    cloud->height = 5;
    cloud->is_dense = true;

    // get tf between base and interactive target
    geometry_msgs::msg::TransformStamped transformStamped;
    try {
      transformStamped = tf_buffer_.lookupTransform(LINK_ZERO_NAME, "ik_target_body", tf2::TimePointZero);
    } catch (tf2::TransformException &ex) {
      RCLCPP_WARN(this->get_logger(), "Transform lookup failed: %s", ex.what());
      return;
    }

    // transform cloud
    Eigen::Affine3d eigen_transform = tf2::transformToEigen(transformStamped);
    Eigen::Matrix4f transform = eigen_transform.matrix().cast<float>();
    pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::transformPointCloud(*cloud, *transformed_cloud, transform);

    // to msg
    sensor_msgs::msg::PointCloud2 output;
    pcl::toROSMsg(*transformed_cloud, output);
    output.header.stamp = this->now();
    output.header.frame_id = LINK_ZERO_NAME;

    publisher_->publish(output);
    RCLCPP_INFO(this->get_logger(), "Published sphere point cloud with %zu points", cloud->points.size());
  }

  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  tf2_ros::Buffer tf_buffer_;
  tf2_ros::TransformListener tf_listener_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CylinderPointCloudPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
