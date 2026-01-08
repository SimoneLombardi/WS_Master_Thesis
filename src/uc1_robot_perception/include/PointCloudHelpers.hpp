#include <pcl/point_types.h>
#include <pcl/common/common_headers.h>
#include <pcl/common/transforms.h>
#include <pcl/io/obj_io.h>
#include <pcl/io/ply_io.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/io/file_io.h>
#include <pcl/conversions.h>
#include <pcl/filters/random_sample.h>
#include <pcl/filters/uniform_sampling.h>
#include <pcl/filters/statistical_outlier_removal.h>
// eigen
#include <Eigen/Core>
#include <Eigen/Dense>

#define KUKA_BASE_LINK 0
#define KUKA_LINK_1    1
#define KUKA_LINK_2    2
#define KUKA_LINK_3    3
#define KUKA_LINK_4    4
#define KUKA_LINK_5    5
#define KUKA_LINK_6    6

#define BASE_LINK      7
#define SHOULDER_LINK  8
#define UPPER_ARM_LINK 9
#define FOREARM_LINK   10
#define WRIST_1_LINK   11
#define WRIST_2_LINK   12
#define WRIST_3_LINK   13


// add static offsets for mismatch between tf and mesh origin
void linkTfOffset(size_t index, Eigen::Matrix4d &tf_eigen)
{
  double x, y, z;
  double yaw, roll, pitch;
  Eigen::Matrix3d R_yaw, R_roll, R_pitch;
  switch (index)
  {
  // base link inertia
  case BASE_LINK:
  {
    x = 0;
    y = 0;
    z = 0;

    Eigen::Matrix3d rotation = Eigen::Matrix3d::Identity();

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // shoulder link
  case SHOULDER_LINK:
  {
    x = 0;
    y = 0;
    z = 0;

    yaw = M_PI;
    R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Eigen::Matrix3d rotation = R_yaw;

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // upper arm link
  case UPPER_ARM_LINK:
  {
    x = 0;
    y = 0;
    z = 0.1762;

    roll = -M_PI / 2;
    yaw = roll;
    R_roll = Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitY()).toRotationMatrix();
    R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Eigen::Matrix3d rotation = R_roll * R_yaw;

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // forearm link
  case FOREARM_LINK:
  {
    x = 0;
    y = 0;
    z = 0.0393;

    roll = -M_PI / 2;
    yaw = roll;
    R_roll = Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitY()).toRotationMatrix();
    R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Eigen::Matrix3d rotation = R_roll * R_yaw;

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // wrist 1 link
  case WRIST_1_LINK:
  {
    x = 0;
    y = 0;
    z = -0.135;

    roll = M_PI / 2;

    R_roll = Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitX()).toRotationMatrix();

    //Eigen::Matrix3d rotation = Eigen::Matrix3d::Identity();
    Eigen::Matrix3d rotation = R_roll;
    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // wrist 2 link
  case WRIST_2_LINK:
  {
    x = 0;
    y = 0;
    z = -0.12;

    Eigen::Matrix3d rotation = Eigen::Matrix3d::Identity();

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  // wrist 3 ( tool 0 tf) link
  case WRIST_3_LINK:
  {
    x = 0;
    y = 0;
    z = -0.1168;

    yaw = M_PI / 2;
    R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Eigen::Matrix3d rotation = R_yaw;

    roll = M_PI / 2;
    yaw = roll;
    R_roll = Eigen::AngleAxisd(roll, Eigen::Vector3d::UnitY()).toRotationMatrix();
    R_yaw = Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    rotation *= R_roll * R_yaw;

    tf_eigen.block<3, 3>(0, 0) = rotation;
    tf_eigen(0, 3) = x;
    tf_eigen(1, 3) = y;
    tf_eigen(2, 3) = z;
    break;
  }

  default:
    std::cout << "index: " << index << " not found in static tf list" << std::endl;
  }
}


void applyCloudTransformation(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const Eigen::Matrix4d &transform_double)
{
  // Convert Eigen::Matrix4d to Eigen::Matrix4f (needed for pcl built in function)
  Eigen::Matrix4f transform_float = transform_double.cast<float>();
  pcl::transformPointCloud(*cloud, *cloud, transform_float);
}

void removeOutliers(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)
{
  pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
  sor.setInputCloud(cloud);
  sor.setMeanK(20);              // neighbors 
  sor.setStddevMulThresh(1.0);   // std threshold
  sor.filter(*cloud);            // always update the same cloud
}

void removeIntersectingCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
                          const pcl::PointCloud<pcl::PointXYZ>::Ptr target_cloud,
                          double proximity_threshold)
{
  // Build a kd-tree for the target cloud (e.g. robot model)
  pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
  kdtree.setInputCloud(target_cloud);

  // Remove points from 'cloud' if their nearest neighbor in 'target_cloud'
  // is closer than the specified threshold.
  auto new_end = std::remove_if(cloud->points.begin(), cloud->points.end(),
    [&](const pcl::PointXYZ &pt) {
      std::vector<int> indices(1);
      std::vector<float> sqr_dists(1);
      if (kdtree.nearestKSearch(pt, 1, indices, sqr_dists) > 0) {
        return std::sqrt(sqr_dists[0]) < proximity_threshold;
      }
      return false;
    });
  cloud->points.erase(new_end, cloud->points.end());
  cloud->width = static_cast<uint32_t>(cloud->points.size());
  cloud->height = 1;
  cloud->is_dense = true;
}

void cropBoundingBox(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const Eigen::Matrix4f &bbox_transform)
{
  pcl::CropBox<pcl::PointXYZ> crop;
  crop.setInputCloud(cloud);
  Eigen::Vector4f min_pt(-5.0f, -5.0f, -1.0f, 1.0f);
  Eigen::Vector4f max_pt( 5.0f,  5.0f,  1.0f, 1.0f);
  crop.setMin(min_pt);
  crop.setMax(max_pt);
  Eigen::Affine3f affine_transform(bbox_transform);
  crop.setTransform(affine_transform);
  crop.filter(*cloud);  
}
