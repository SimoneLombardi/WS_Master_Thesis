#include "EnvCloudManager.hpp"

// PCL includes
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl_conversions/pcl_conversions.h>

// TF2
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <tf2/LinearMath/Quaternion.h>

// ament_index_cpp
#include <ament_index_cpp/get_package_share_directory.hpp>

// C++ standard
#include <random>
#include <filesystem>  // C++17 for filename extraction
#include <string>

using namespace UseCase1;

EnvCloudManager::EnvCloudManager() : Node("environment_pointcloud_manager")
{
  // ------------------------- environment static point cloud (ground truth)
  auto share_dir = ament_index_cpp::get_package_share_directory("environment_pointcloud_processing");
  std::string pcd_file_path = share_dir + "/resources/chassis_downsampled_cloud.pcd";
  true_env_cloud_msg_ = loadPointCloudFromFile(pcd_file_path, /*scale=*/0.001f, /*noise_stddev=*/0.0f);
  if (!true_env_cloud_msg_) {
    RCLCPP_ERROR(this->get_logger(), "Failed to load initial cloud from: %s", pcd_file_path.c_str());
    return;
  }
  std::string topic_name = createTopicFromFile(pcd_file_path);
  RCLCPP_INFO(this->get_logger(), "Publishing on topic: %s", topic_name.c_str());
  true_env_cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(topic_name, 10);
  // -----------------------------------------------------------------------

  // ------------------------- simulated tof point cloud (part of chassis from file, dynamic part to be added)
  pcd_file_path = share_dir + "/resources/partial_chassis_downsampled_cloud.pcd";
  tof_meas_cloud_msg_ = loadPointCloudFromFile(pcd_file_path, /*scale=*/0.001f, /*noise_stddev=*/0.0f);
  if (!tof_meas_cloud_msg_) {
    RCLCPP_ERROR(this->get_logger(), "Failed to load initial cloud from: %s", pcd_file_path.c_str());
    return;
  }
  topic_name = createTopicFromFile(pcd_file_path);
  RCLCPP_INFO(this->get_logger(), "Publishing on topic: %s", topic_name.c_str());
  tof_meas_cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>(topic_name, 10);
  // -----------------------------------------------------------------------


  // static transform for ground truth env cloud
  static_broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
  publishStaticTransform("kuka_base_link", "env_cloud_frame");

  // initialize moving cloud params
  blob_center_x_ = 2.5;
  blob_center_y_ = 0.1;
  blob_center_z_ = 1.0;
  iteration_count_ = 0;

  // publish static environment at 1 Hz
  static_cloud_timer_ = this->create_wall_timer(
    std::chrono::seconds(1),
    std::bind(&EnvCloudManager::publishStaticCloud, this)
  );

  // simulated tof measurements (static + dynamic)
  tof_cloud_timer_ = this->create_wall_timer(
    std::chrono::milliseconds(67),
    std::bind(&EnvCloudManager::publishDynamicCloud, this)
  );

  RCLCPP_INFO(this->get_logger(), "EnvCloudManager node started.");
}


sensor_msgs::msg::PointCloud2::SharedPtr EnvCloudManager::loadPointCloudFromFile(
  const std::string &file_path,
  float scale,
  float noise_stddev)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
  int load_result = -1;

  load_result = pcl::io::loadPCDFile<pcl::PointXYZ>(file_path, *cloud);

  if (load_result == -1) {
    RCLCPP_ERROR(this->get_logger(), "Failed to load file: %s", file_path.c_str());
    return nullptr;
  }

  // Scale & optional noise
  applyScaling(cloud, scale);
  if (noise_stddev > 0.0f) {
    addGaussianNoise(cloud, noise_stddev);
  }

  // Convert to ROS2 msg
  pcl_conversions::toPCL(rclcpp::Clock().now(), cloud->header.stamp);
  sensor_msgs::msg::PointCloud2 cloud_msg;
  pcl::toROSMsg(*cloud, cloud_msg);
  cloud_msg.header.frame_id = "env_cloud_frame";

  return std::make_shared<sensor_msgs::msg::PointCloud2>(cloud_msg);
}


std::string EnvCloudManager::createTopicFromFile(const std::string &file_path)
{
  // Extract the file name
  std::string filename = std::filesystem::path(file_path).filename().string();
  // Remove extension
  auto pos = filename.find_last_of('.');
  if (pos != std::string::npos) {
    filename = filename.substr(0, pos);
  }

  // return topic name
  return "/" + filename;
}

void EnvCloudManager::publishStaticCloud()
{
  true_env_cloud_msg_->header.stamp = now();
  true_env_cloud_pub_->publish(*true_env_cloud_msg_);

  RCLCPP_INFO_ONCE(this->get_logger(), "Publishing environment point clouds...");
}

void EnvCloudManager::publishDynamicCloud()
{
  float stddev = 0.02;

  // convert message cloud to pcl (TODO change storage format)
  pcl::PointCloud<pcl::PointXYZ> partial_chassis_cloud;
  pcl::fromROSMsg(*tof_meas_cloud_msg_, partial_chassis_cloud);

  // add spherical blob to point cloud
  pcl::PointCloud<pcl::PointXYZ> moving_cloud = generateSphericalBlob(0.3f, 100);

  // animate the blob cloud by shifting its center (TODO need to initialize origin)
  iteration_count_++;
  blob_center_x_ += blob_direction_ * 0.01f;  
  blob_center_y_ = blob_center_y_ + 0.05f * std::sin(iteration_count_ * 0.2f);

  // update blob direction (TODO replace as sinusoid)
  if (blob_center_x_ >= x_max_) {
    blob_center_x_ = x_max_;
    blob_direction_ = -1.0f;
  }
  else if (blob_center_x_ <= x_min_) {
    blob_center_x_ = x_min_;
    blob_direction_ = 1.0f;
  }
  
  for (auto &pt : moving_cloud.points) {
    pt.x += blob_center_x_;
    pt.y += blob_center_y_;
    pt.z += blob_center_z_;
  }

  // merge moving cloud to partial chassis
  partial_chassis_cloud.points.insert(
    partial_chassis_cloud.points.end(),
    moving_cloud.points.begin(),
    moving_cloud.points.end());
  partial_chassis_cloud.width = partial_chassis_cloud.points.size();
  partial_chassis_cloud.height = 1;

   // add gaussian noise to simulated tof pointcloud
  std::default_random_engine generator(std::random_device{}());
  std::normal_distribution<float> dist(0.0f, stddev);
  
  for (auto &pt : partial_chassis_cloud.points) {
    pt.x += dist(generator);
    pt.y += dist(generator);
    pt.z += dist(generator);
  }

  // convert back to ros2 msg
  sensor_msgs::msg::PointCloud2 sim_tof_cloud_msg;
  pcl::toROSMsg(partial_chassis_cloud, sim_tof_cloud_msg);
  sim_tof_cloud_msg.header.stamp = now();
  tof_meas_cloud_pub_->publish(sim_tof_cloud_msg);

  RCLCPP_INFO_ONCE(this->get_logger(), "Publishing tof point clouds...");
}

void EnvCloudManager::publishStaticTransform(const std::string &parent_frame, const std::string &child_frame)
{
  geometry_msgs::msg::TransformStamped transform_stamped;
  transform_stamped.header.stamp = this->now();
  transform_stamped.header.frame_id = parent_frame;
  transform_stamped.child_frame_id = child_frame;

  // chassis to KUKA base
  // TODO UPDATE AFTER CALIBRATION
  transform_stamped.transform.translation.x = 2.5;
  transform_stamped.transform.translation.y = -2.0;
  transform_stamped.transform.translation.z = -0.35;
  tf2::Quaternion q;
  q.setRPY(0.0, 0.0, 1.57);
  transform_stamped.transform.rotation.x = q.x();
  transform_stamped.transform.rotation.y = q.y();
  transform_stamped.transform.rotation.z = q.z();
  transform_stamped.transform.rotation.w = q.w();

  static_broadcaster_->sendTransform(transform_stamped);
  RCLCPP_INFO(get_logger(), "Broadcasting static transform [%s -> %s].",
              parent_frame.c_str(), child_frame.c_str());
}


void EnvCloudManager::applyScaling(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, float scale)
{
  if (scale == 1.0f) return;
  for (auto &p : cloud->points) {
    p.x *= scale;
    p.y *= scale;
    p.z *= scale;
  }
}


void EnvCloudManager::addGaussianNoise(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, float stddev)
{
  if (stddev <= 0.0f) return;

  std::default_random_engine generator(std::random_device{}());
  std::normal_distribution<float> dist(0.0f, stddev);

  for (auto &p : cloud->points) {
    p.x += dist(generator);
    p.y += dist(generator);
    p.z += dist(generator);
  }
}

// helper function for generating a blob-like point cloud (currently only sphere is supported)
pcl::PointCloud<pcl::PointXYZ> EnvCloudManager::generateSphericalBlob(float radius, int num_points)
{
  pcl::PointCloud<pcl::PointXYZ> blob;
  blob.points.reserve(num_points);

  std::default_random_engine rng(std::random_device{}());
  std::uniform_real_distribution<float> angle_dist(0.0f, 2.0f * M_PI);
  std::uniform_real_distribution<float> cos_dist(-1.0f, 1.0f);

  // sample each point from spherical coordinates
  for (int i = 0; i < num_points; i++) {
    float theta = angle_dist(rng);
    float u = cos_dist(rng);
    float phi = std::acos(u);

    float x = radius * std::sin(phi) * std::cos(theta);
    float y = radius * std::sin(phi) * std::sin(theta);
    float z = radius * std::cos(phi);

    blob.points.push_back(pcl::PointXYZ(x, y, z));
  }

  return blob;
}


