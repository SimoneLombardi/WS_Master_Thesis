#ifndef PROXIMITY_TASK_GENERATOR_HPP
#define PROXIMITY_TASK_GENERATOR_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/vector3.hpp>
#include <mutex>
#include <vector>
#include <string>
#include <filesystem>

// tf2
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2_eigen/tf2_eigen.h>
#include <geometry_msgs/msg/transform_stamped.hpp>

// pcl
#include <pcl/point_cloud.h>
#include <pcl/common/transforms.h>
#include <pcl/point_types.h>
#include <pcl/common/common_headers.h>
#include <pcl/io/obj_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/io/file_io.h>
#include <pcl/conversions.h>
#include <pcl/filters/random_sample.h>
#include <pcl/filters/uniform_sampling.h>
#include <pcl/filters/crop_box.h>
#include <pcl/filters/radius_outlier_removal.h>

// tasks and visualization
#include <visualization_msgs/msg/marker_array.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <geometry_msgs/msg/point.hpp>

// misc.
#include <ament_index_cpp/get_package_share_directory.hpp>

// custom messages
#include "uc1_robot_perception/msg/proximity_task.hpp"
#include "uc1_robot_perception/msg/proximity_task_array.hpp"

#define JOINT_R_LINKS 14
constexpr int stl_links = JOINT_R_LINKS;

// task struct
struct ProximityTask {
  Eigen::Vector3d point;     // position of the closest point 
  Eigen::Vector3d direction; // direction vector from link point to env point
  float distance;            // absolute distance
  std::string link_name;     // robot link 
};

class ProximityTaskGenerator : public rclcpp::Node
{
public:
  ProximityTaskGenerator();
  ~ProximityTaskGenerator() override = default;

  // tf handlers
  void broadcastTransform(const std::string & parent_frame, const std::string & child_frame);
  bool subscribeToTransform(const std::string & parent_frame, const std::string & child_frame,
                            geometry_msgs::msg::TransformStamped & transformStamped);

private:
  // pointcloud sub callback
  void pointCloudCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);

  // robot point cloud aggregation and publisher
  void robotCloudModel();

  // cloud processing
  void publishPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
                         const std::string & frame_name,
                         const rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr & publisher);
  bool transformPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud,
                           pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud,
                           std::string target_frame);
  void publishProximityMarkers(const std::vector<ProximityTask> & tasks,
                             const rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr & marker_pub,
                             const std::string & frame_id, const rclcpp::Time & stamp);
  void publishProximityTasks(const std::vector<ProximityTask> & tasks,
                                  const rclcpp::Publisher<uc1_robot_perception::msg::ProximityTaskArray>::SharedPtr & task_pub);
  
  // control task generation
  std::vector<ProximityTask> computeProximityTasks(pcl::PointCloud<pcl::PointXYZ>::Ptr env_cloud);

  // communication
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr pointcloud_subscriber_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr filtered_cloud_publisher_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr robot_cloud_publisher_;
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr task_marker_publisher_;
  rclcpp::Publisher<uc1_robot_perception::msg::ProximityTaskArray>::SharedPtr task_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

  // thread-safe point cloud storage
  sensor_msgs::msg::PointCloud2 current_cloud_;
  std::mutex cloud_mutex_;

  // static stl pointclouds
  std::vector<sensor_msgs::msg::PointCloud2> stl_pointclouds_;

  // tf2 
  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  std::shared_ptr<tf2_ros::Buffer> tf_buffer_;
  std::shared_ptr<tf2_ros::TransformListener> tf_listener_;

  // pcl processing
  std::array<pcl::PointCloud<pcl::PointXYZ>::Ptr, stl_links> robot_link_clouds_;
  std::array<pcl::PointCloud<pcl::PointXYZ>::Ptr, stl_links> robot_link_clouds_base_;
  pcl::PointCloud<pcl::PointXYZ>::Ptr merged_robot_cloud_;
  std::array<Eigen::Matrix4d, stl_links> links_pcl_offsets_;

  std::array<std::string, stl_links> robot_frames_; 
};

#endif // PROXIMITY_TASK_GENERATOR_HPP
