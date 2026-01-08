#include "CloudMotionExtractor.hpp"

// PCL
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/common/io.h> // for operator+

// C++ includes
#include <random>
#include <cmath>

// TODO naive implementation, need to implement more refined methods
// For instance, if the chassis is calibrated wrt the robot, I can just use the mesh removal algorithm with the real chassis cloud
// To increase the complexity we can also add chassis calibration with robot measurements, by using particle filter or iterative ICP 

CloudMotionExtractor::CloudMotionExtractor(): Node("cloud_motion_extractor_node")
{
  // pubs
  static_cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/segmented_static_cloud", 10);
  moving_cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/segmented_moving_cloud", 10);

  // subs
  cloud_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
    "/partial_chassis_downsampled_cloud",
    10,
    std::bind(&CloudMotionExtractor::cloudMotionCallback, this, std::placeholders::_1)
  );

  // for differential motion estimation
  prev_cloud_ = nullptr;

  RCLCPP_INFO(get_logger(), "CloudMotionExtractor node started.");
}

void CloudMotionExtractor::cloudMotionCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  // allocate output clouds
  pcl::PointCloud<pcl::PointXYZ>::Ptr static_part(new pcl::PointCloud<pcl::PointXYZ>());
  pcl::PointCloud<pcl::PointXYZ>::Ptr moving_part(new pcl::PointCloud<pcl::PointXYZ>());

  // msg to pcl
  pcl::PointCloud<pcl::PointXYZ>::Ptr current_cloud(new pcl::PointCloud<pcl::PointXYZ>());
  pcl::fromROSMsg(*msg, *current_cloud);

  // if is the very first message, just store
  if (!prev_cloud_) {
    prev_cloud_ = current_cloud;
    RCLCPP_INFO(get_logger(), "Received first cloud, stored as previous.");
    return;
  }

  // build KD-tree from previous point cloud
  pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
  kdtree.setInputCloud(prev_cloud_);

  // distance threshold from previous point to be considered static
  float motion_threshold = 0.08f; 

  // compare current cloud with previous
  for (const auto &pt : current_cloud->points) {
    std::vector<int> indices(1);
    std::vector<float> sqr_distances(1);
    if (kdtree.nearestKSearch(pt, 1, indices, sqr_distances) > 0) {
      float dist = std::sqrt(sqr_distances[0]);
      if (dist < motion_threshold) {
        static_part->points.push_back(pt);
      } else {
        moving_part->points.push_back(pt);
      }
    } else {
      // previous point is not a neighbor, treat it as moving
      moving_part->points.push_back(pt);
    }
  }

  // adjust widths
  static_part->width  = static_part->points.size();
  static_part->height = 1;
  moving_part->width  = moving_part->points.size();
  moving_part->height = 1;

  // build ros msgs and publish
  sensor_msgs::msg::PointCloud2 static_msg;
  pcl::toROSMsg(*static_part, static_msg);
  static_msg.header = msg->header; // same frame, same stamp
  sensor_msgs::msg::PointCloud2 moving_msg;
  pcl::toROSMsg(*moving_part, moving_msg);
  moving_msg.header = msg->header;
  static_cloud_pub_->publish(static_msg);
  moving_cloud_pub_->publish(moving_msg);

  // update prev_cloud_
  prev_cloud_ = current_cloud;

  RCLCPP_INFO(get_logger(), "Publishing motion-segmented clouds...");
}
