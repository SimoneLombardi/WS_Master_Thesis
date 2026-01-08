#include "TfGoalBroadcaster.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/LinearMath/Quaternion.h"

void TfGoalBroadcaster::broadcastStaticTransform(
    const Eigen::Vector3d& position,
    const Eigen::Vector3d& rpy,
    const std::string& parent_frame,
    const std::string& child_frame)
{
  geometry_msgs::msg::TransformStamped transform_stamped;

  transform_stamped.header.stamp = node_->now();

  transform_stamped.header.frame_id = parent_frame;
  transform_stamped.child_frame_id  = child_frame;

  transform_stamped.transform.translation.x = position.x();
  transform_stamped.transform.translation.y = position.y();
  transform_stamped.transform.translation.z = position.z();

  tf2::Quaternion q;
  q.setRPY(rpy.x(), rpy.y(), rpy.z()); 
  transform_stamped.transform.rotation.x = q.x();
  transform_stamped.transform.rotation.y = q.y();
  transform_stamped.transform.rotation.z = q.z();
  transform_stamped.transform.rotation.w = q.w();

  static_broadcaster_->sendTransform(transform_stamped);
}
