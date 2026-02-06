#ifndef ROBOT_CLOUD_BROADCASTER_HPP
#define ROBOT_CLOUD_BROADCASTER_HPP

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





#endif // ROBOT_CLOUD_BROADCASTER_HPP