#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <pcl/common/transforms.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2_eigen/tf2_eigen.hpp>
#include <cmath>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <ament_index_cpp/get_package_share_directory.hpp>


#define LINK_ZERO_NAME "kuka_base_link"

class ObstaclePointCloudBroadcaster : public rclcpp::Node
{
    public:
        ObstaclePointCloudBroadcaster() : Node("obstacle_point_cloud_broadcaster"),
            tf_buffer_(this->get_clock()), tf_listener_(tf_buffer_)
        {
            ptc_fileName = this->declare_parameter<std::string>("ptc_filename", "default.pcd");
            ptc_pkg = this->declare_parameter<std::string>("ptc_pkgname", "default");

            publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/environment_point_cloud", 10);

            // timer, publish the point cloud
            timer_ = this->create_wall_timer(std::chrono::milliseconds(10),
                                             std::bind(&ObstaclePointCloudBroadcaster::timer_callback, this));
            
            auto share_dir = ament_index_cpp::get_package_share_directory(ptc_pkg);
            point_cloud_path = share_dir + ptc_fileName;
        }

    private:
        void timer_callback()
        {
            // LOAD THE POINT CLOUD from FILE
            pcl::PointCloud<pcl::PointXYZ>::Ptr ob_cloud(new pcl::PointCloud<pcl::PointXYZ>);
            if(pcl::io::loadPCDFile<pcl::PointXYZ> (point_cloud_path, *ob_cloud) == -1){
                RCLCPP_ERROR(this->get_logger(), "Failed to read point cloud file, %s", point_cloud_path.c_str());
            }

            ob_cloud->header.frame_id = "ik_target_body";
            ob_cloud->width = static_cast<uint32_t>(ob_cloud->points.size());
            ob_cloud->height = 1;
            ob_cloud->is_dense = true;

            //RCLCPP_INFO(this->get_logger(), "\nloaded cloud info:\n points: %d\n size of data: %zu", ob_cloud->points.size(), sizeof(ob_cloud->points[0].x));
            // GET TF FROM BASE TO INTERACTIVE TARGHET
            geometry_msgs::msg::TransformStamped tf;
            try
            {
                tf = tf_buffer_.lookupTransform(LINK_ZERO_NAME, "ik_target_body", tf2::TimePointZero);
            }
            catch(tf2::TransformException &ex)
            {
                RCLCPP_WARN(this->get_logger(), "Transform lookup failed: %s", ex.what());
                return;
            }

            //APPLY THE TF TO THE STATIC CLOUD
            Eigen::Affine3d eigen_tf = tf2::transformToEigen(tf);
            Eigen::Matrix4f transform = eigen_tf.matrix().cast<float>();
            pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud(new pcl::PointCloud<pcl::PointXYZ>);
            pcl::transformPointCloud(*ob_cloud, *transformed_cloud, transform);

            //TRASFORM TO ROS2 MSG AND PUBLIHS
            sensor_msgs::msg::PointCloud2 msg_cloud;
            pcl::toROSMsg(*transformed_cloud, msg_cloud);
            msg_cloud.header.stamp = this->now();
            msg_cloud.header.frame_id = LINK_ZERO_NAME;

            publisher_->publish(msg_cloud);
            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 300, "obst cloud published, %s", ptc_fileName.c_str());
        }


        rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        tf2_ros::Buffer tf_buffer_;
        tf2_ros::TransformListener tf_listener_; 

        // static point cloud path
        std::string point_cloud_path;
        std::string ptc_fileName;
        std::string ptc_pkg;
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ObstaclePointCloudBroadcaster>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}