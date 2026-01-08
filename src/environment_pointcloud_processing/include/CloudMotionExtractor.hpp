#ifndef CLOUD_MOTION_EXTRACTOR_HPP
#define CLOUD_MOTION_EXTRACTOR_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <memory>
#include <string>
#include <vector>

class CloudMotionExtractor : public rclcpp::Node
{
public:

  CloudMotionExtractor();

private:
  
  /**
   * @brief subscribe to partial chassis cloud
   */
  void cloudMotionCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg);


private:

  // pubs
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr static_cloud_pub_;
  rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr moving_cloud_pub_;

  // subs 
  rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr cloud_sub_;

  // cloud msgs
  sensor_msgs::msg::PointCloud2::SharedPtr static_cloud_msg_;
  sensor_msgs::msg::PointCloud2::SharedPtr moving_cloud_msg_;

  // timers
  rclcpp::TimerBase::SharedPtr cloud_timer_;

  pcl::PointCloud<pcl::PointXYZ>::Ptr prev_cloud_;


};



#endif // CLOUD_MOTION_EXTRACTOR_HPP