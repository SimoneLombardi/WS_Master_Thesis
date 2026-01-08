#ifndef ENV_CLOUD_MANAGER_HPP
#define ENV_CLOUD_MANAGER_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <memory>
#include <string>
#include <vector>

namespace UseCase1
{

class EnvCloudManager : public rclcpp::Node
{
public:

  EnvCloudManager();

private:
  
  /**
   * @brief Load a PCD/PLY file, apply optional scaling + noise, return as sensor_msgs.
   *
   * @param file_path     Path to the .pcd or .ply file.
   * @param scale         Scale factor (e.g. 0.001f to go from mm to m).
   * @param noise_stddev  If > 0.0, adds random Gaussian noise to X/Y/Z.
   * @return sensor_msgs::msg::PointCloud2::SharedPtr or nullptr if load failed.
   */
  sensor_msgs::msg::PointCloud2::SharedPtr loadPointCloudFromFile(
    const std::string &file_path,
    float scale = 1.0f,
    float noise_stddev = 0.0f
  );

  /**
   * @brief Create a topic name from the given file name, e.g. "my_cloud.pcd" -> "/my_cloud"
   */
  std::string createTopicFromFile(const std::string &file_path);
  
  /**
   * @brief Publish static environment pointcloud
   */
  void publishStaticCloud();

  /**
   * @brief Publish dynamic environment pointcloud
   */
  void publishDynamicCloud();

  /**
   * @brief Publish a static transform from parent_frame to child_frame.
   */
  void publishStaticTransform(
    const std::string &parent_frame,
    const std::string &child_frame
  );

  /**
   * @brief Add Gaussian noise to each XYZ coordinate in the cloud.
   */
  void addGaussianNoise(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, float stddev);

  /**
   * @brief Apply uniform scaling to a PCL point cloud in-place.
   */
  void applyScaling(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud, float scale);

  /**
   * @brief Generate a pointcloud sampled by a spherical manifold
   */
  pcl::PointCloud<pcl::PointXYZ> generateSphericalBlob(float radius, int num_points);

private:

  // pubs
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr true_env_cloud_pub_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr tof_meas_cloud_pub_;

  // cloud msgs
  sensor_msgs::msg::PointCloud2::SharedPtr true_env_cloud_msg_;
  sensor_msgs::msg::PointCloud2::SharedPtr tof_meas_cloud_msg_;

  // timers
  rclcpp::TimerBase::SharedPtr static_cloud_timer_;
  rclcpp::TimerBase::SharedPtr tof_cloud_timer_;    // simulated tof measurements

  // TF
  std::shared_ptr<tf2_ros::StaticTransformBroadcaster> static_broadcaster_;

  // ---------------- helpers for tof cloud emulation
  float blob_center_x_;
  float blob_center_y_;
  float blob_center_z_;
  int iteration_count_;
  float blob_direction_ = 1.0f;     
  float x_min_ = 2.5f;          
  float x_max_ = 3.5f;        

};

}


#endif // ENV_CLOUD_MANAGER_HPP