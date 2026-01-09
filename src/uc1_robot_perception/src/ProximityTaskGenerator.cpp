#include "ProximityTaskGenerator.hpp"
#include "PointCloudHelpers.hpp"
#include <cstdlib>

#define LINK_ZERO_NAME "kuka_base_link" // nome del primo link del quale devo calcolare le proximity task

ProximityTaskGenerator::ProximityTaskGenerator()
    : Node("proximity_task_generator"),
      tf_buffer_(std::make_shared<tf2_ros::Buffer>(this->get_clock())),
      tf_listener_(std::make_shared<tf2_ros::TransformListener>(*tf_buffer_))
{
  // store frame names
  std::cout << "prox task gen 1" << std::endl;
  robot_frames_ = {"kuka_base_link", "kuka_link_1", "kuka_link_2", "kuka_link_3", "kuka_link_4", "kuka_link_5", "kuka_link_6", 
                  "base_link", "shoulder_link", "upper_arm_link", "forearm_link", "wrist_1_link", "wrist_2_link", "wrist_3_link"};

  // load ply files as pointclouds
  std::string share_dir = ament_index_cpp::get_package_share_directory("uc1_robot_perception");
  std::string pointclouds_path = share_dir + "/resources/ply/";

  std::string ur10_fldr = "ur10/";
  std::string kuka_fldr = "kuka/";

  std::array<std::string, stl_links> file_paths = {
      pointclouds_path + kuka_fldr + "base_link.ply",
      pointclouds_path + kuka_fldr + "link_1.ply",
      pointclouds_path + kuka_fldr + "link_2.ply",
      pointclouds_path + kuka_fldr + "link_3.ply",
      pointclouds_path + kuka_fldr + "link_4.ply",
      pointclouds_path + kuka_fldr + "link_5.ply",
      pointclouds_path + kuka_fldr + "link_6.ply",
      pointclouds_path + ur10_fldr + "base.ply",
      pointclouds_path + ur10_fldr + "shoulder.ply",
      pointclouds_path + ur10_fldr + "upperarm.ply",
      pointclouds_path + ur10_fldr + "forearm.ply",
      pointclouds_path + ur10_fldr + "wrist1.ply",
      pointclouds_path + ur10_fldr + "wrist2.ply",
      pointclouds_path + ur10_fldr + "wrist3.ply"
    };

  std::cout << "prox task gen 2" << std::endl;
  for (size_t i = 0; i < robot_link_clouds_.size(); ++i)
  {
    robot_link_clouds_[i] = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
    // read the pcl file
    if (pcl::io::loadPLYFile<pcl::PointXYZ>(file_paths[i], *robot_link_clouds_[i]) == -1)
    {
      PCL_ERROR("Couldn't read the file \n");
      exit(0);
    }

    // also initialize transformed clouds pointers
    robot_link_clouds_base_[i] = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
  }
  std::cout << "prox task gen 3" << std::endl;
  RCLCPP_INFO(this->get_logger(), "Loaded %zu robot link point clouds.", robot_link_clouds_.size());

  // static cloud uniform downsampling
  float radius = 0.02;                                         //k_l_6
  std::vector radiuses = {0.05, 0.055, 0.05, 0.05, 0.022, 0.027, 0.02, 0.02, 0.02, 0.04, 0.027, 0.02, 0.02, 0.01};
  int max_cloud_pts = 1000;

  for (size_t i = 0; i < robot_link_clouds_.size(); ++i)
  {
    if (robot_link_clouds_[i]->points.size() <= max_cloud_pts)
    {
      continue;
    }else{
      pcl::UniformSampling<pcl::PointXYZ> uniform_sampling;
      uniform_sampling.setInputCloud(robot_link_clouds_[i]);
      uniform_sampling.setRadiusSearch(radiuses[i]);
      uniform_sampling.filter(*robot_link_clouds_[i]);
    }
    std::cout << robot_frames_[i] << ", cloude size: " << robot_link_clouds_[i]->points.size() << " rad: " << radiuses[i] <<  std::endl;
  }
  std::cout << "link offsets" << std::endl;
  // fill static tf offsets for robot links
  for (size_t i = 0; i < links_pcl_offsets_.size(); ++i)
  {
    links_pcl_offsets_[i] = Eigen::Matrix4d::Identity();
    linkTfOffset(i, links_pcl_offsets_[i]);
  }
  std::cout << "prox task gen 4" << std::endl;
  // apply static tf offsets to clouds
  for (size_t i = 0; i < links_pcl_offsets_.size(); ++i)
  {
    applyCloudTransformation(robot_link_clouds_[i], links_pcl_offsets_[i]);
  }

  std::cout << "prox task gen 5" << std::endl;
  // subscribe to /environment_point_cloud
  pointcloud_subscriber_ = this->create_subscription<sensor_msgs::msg::PointCloud2>(
      "/environment_point_cloud",
      10,
      std::bind(&ProximityTaskGenerator::pointCloudCallback, this, std::placeholders::_1));

  // publisher for republishing (filtered) point cloud
  filtered_cloud_publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("filtered_env_cloud", 10);

  // robot cloud publisher
  robot_cloud_publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("robot_cloud", 10);

  // task markers
  task_marker_publisher_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("proximity_control_markers", 10);

  // publisher for the custom task message
  task_publisher_ = this->create_publisher<uc1_robot_perception::msg::ProximityTaskArray>("proximity_task_control", 10);

  // initialize transform broadcaster
  tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);

  RCLCPP_INFO(this->get_logger(), "Proximity Task Generator node initialized.");

  // timer to periodically publish the filtered point cloud and custom task message
  timer_ = this->create_wall_timer(
      std::chrono::milliseconds(10),
      std::bind(&ProximityTaskGenerator::robotCloudModel, this));
  
  std::cout << "prox task gen 6, init complete" << std::endl;
}

// point cloud processing pipeline
void ProximityTaskGenerator::pointCloudCallback(const sensor_msgs::msg::PointCloud2::SharedPtr msg)
{
  // convert to pcl
  pcl::PointCloud<pcl::PointXYZ>::Ptr env_cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr env_cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromROSMsg(*msg, *env_cloud);
  *env_cloud_filtered = *env_cloud;

  // get tf for centering bbox around robot
  geometry_msgs::msg::TransformStamped tf_stamped;
  try
  {
    tf_stamped = tf_buffer_->lookupTransform("world", LINK_ZERO_NAME, tf2::TimePointZero);
  }
  catch (tf2::TransformException &ex)
  {
    RCLCPP_WARN(this->get_logger(), "(world)Failed to lookup transform: %s", ex.what());
    return;
  }
  Eigen::Affine3d eigen_affine = tf2::transformToEigen(tf_stamped);
  Eigen::Matrix4f bbox_transform = eigen_affine.matrix().cast<float>();

  // proximity threshold for robot model filtering
  double proximity_threshold = 0.05; // Example: remove points closer than 20 cm.

  // apply processing
  //removeOutliers(env_cloud_filtered);
  //removeIntersectingCloud(env_cloud_filtered, merged_robot_cloud_, proximity_threshold);
  //cropBoundingBox(env_cloud_filtered, bbox_transform);


  // republish filtered cloud
  publishPointCloud(env_cloud_filtered, LINK_ZERO_NAME, filtered_cloud_publisher_);

  // build proximity avoidance task
  std::vector<ProximityTask> tasks = computeProximityTasks(env_cloud_filtered);

  // publish task markers
  std::string frame_id = LINK_ZERO_NAME;
  publishProximityMarkers(tasks, task_marker_publisher_, frame_id, this->now());

  // publish custom task msg
  publishProximityTasks(tasks, task_publisher_); 
}

void ProximityTaskGenerator::publishPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,
                                               const std::string &frame_name,
                                               const rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr &publisher)
{
  sensor_msgs::msg::PointCloud2 msg;
  pcl::toROSMsg(*cloud, msg);
  msg.header.frame_id = frame_name;
  msg.header.stamp = this->now();
  publisher->publish(msg);
}

bool ProximityTaskGenerator::transformPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr source_cloud,
                                                 pcl::PointCloud<pcl::PointXYZ>::Ptr transformed_cloud,
                                                 std::string target_frame)
{
  // std::cout << "Target frame: '" << target_frame << "' with size: " << target_frame.size() << std::endl;

  if (target_frame.empty())
  {
    RCLCPP_ERROR(this->get_logger(), "Empty target_frame provided to transformPointCloud.");
    return false;
  }

  // get link tf
  geometry_msgs::msg::TransformStamped transformStamped;
  try
  {
    // tf_buffer_ is assumed to be a member of your node, initialized along with tf_listener_.
    transformStamped = tf_buffer_->lookupTransform(LINK_ZERO_NAME, target_frame, tf2::TimePointZero);
  }
  catch (tf2::TransformException &ex)
  {
    //RCLCPP_WARN(this->get_logger(), "Failed to get transform from '%s' to '%s': %s",LINK_ZERO_NAME, target_frame.c_str(), ex.what());
    //RCLCPP_WARN(this->get_logger(), "tfr point cloud transform from '%s' to '%s': MISSING",LINK_ZERO_NAME, target_frame.c_str());
    return false;
  }

  // to eigen
  Eigen::Affine3d eigen_transform = tf2::transformToEigen(transformStamped);
  // to float for pcl
  Eigen::Matrix4f transform = eigen_transform.matrix().cast<float>();

  pcl::transformPointCloud(*source_cloud, *transformed_cloud, transform);

  return true;
}

void ProximityTaskGenerator::broadcastTransform(const std::string &parent_frame, const std::string &child_frame)
{
  geometry_msgs::msg::TransformStamped transformStamped;
  transformStamped.header.stamp = this->now();
  transformStamped.header.frame_id = parent_frame;
  transformStamped.child_frame_id = child_frame;
  transformStamped.transform.translation.x = 0.0;
  transformStamped.transform.translation.y = 0.0;
  transformStamped.transform.translation.z = 0.0;
  transformStamped.transform.rotation.x = 0.0;
  transformStamped.transform.rotation.y = 0.0;
  transformStamped.transform.rotation.z = 0.0;
  transformStamped.transform.rotation.w = 1.0;
  tf_broadcaster_->sendTransform(transformStamped);
}

bool ProximityTaskGenerator::subscribeToTransform(const std::string &parent_frame, const std::string &child_frame,
                                                  geometry_msgs::msg::TransformStamped &transformStamped)
{
  try
  {
    transformStamped = tf_buffer_->lookupTransform(parent_frame, child_frame, tf2::TimePointZero);
    return true;
  }
  catch (tf2::TransformException &ex)
  {
    //RCLCPP_WARN(this->get_logger(), "transform from '%s' to '%s': %s",parent_frame.c_str(), child_frame.c_str(), ex.what());
    RCLCPP_WARN(this->get_logger(), "sub to transform from '%s' to '%s': MISSING",parent_frame.c_str(), child_frame.c_str());
    return false;
  }
}

void ProximityTaskGenerator::robotCloudModel()
{
  // transform robot link clouds wrt base
  merged_robot_cloud_ = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>());
  for (int i = 0; i < robot_link_clouds_.size(); i++)
  {
    transformPointCloud(robot_link_clouds_[i], robot_link_clouds_base_[i], robot_frames_[i]);

    // merging base-referred robot clouds
    merged_robot_cloud_->points.insert(merged_robot_cloud_->points.end(),
                                       robot_link_clouds_base_[i]->points.begin(), robot_link_clouds_base_[i]->points.end());
  }
  merged_robot_cloud_->width = merged_robot_cloud_->points.size();
  merged_robot_cloud_->height = 1;

  // publish robot link clouds
  publishPointCloud(merged_robot_cloud_, LINK_ZERO_NAME, robot_cloud_publisher_);
}

// compute proximity control task
std::vector<ProximityTask> ProximityTaskGenerator::computeProximityTasks(pcl::PointCloud<pcl::PointXYZ>::Ptr env_cloud)
{
  std::vector<ProximityTask> tasks;
  
  // kd tree for nn search
  pcl::KdTreeFLANN<pcl::PointXYZ> kdtree;
  kdtree.setInputCloud(env_cloud);
  
  for (int i=0; i < robot_link_clouds_base_.size(); i++)
  {
    std::string link_name = robot_frames_[i];
    pcl::PointCloud<pcl::PointXYZ>::Ptr link_cloud = robot_link_clouds_base_[i];
    
    float min_dist_sq = std::numeric_limits<float>::max();
    pcl::PointXYZ closest_env_point;
    pcl::PointXYZ closest_link_point;
    
    //RCLCPP_ERROR(this->get_logger(), "envCloud %zu points", env_cloud->points.size());
    // for each link point, search env cloud neighbor
    for (const auto & pt : link_cloud->points)
    {
      std::vector<int> indices(1);
      std::vector<float> sqr_distances(1);
      if (kdtree.nearestKSearch(pt, 1, indices, sqr_distances) > 0)
      {
        if (sqr_distances[0] < min_dist_sq)
        {
          min_dist_sq = sqr_distances[0];
          closest_link_point = pt;
          closest_env_point = env_cloud->points[indices[0]];
        }
      }
    }
    
    // if a pair is found, fill the task 
    if (min_dist_sq < std::numeric_limits<float>::max())
    {
      ProximityTask task;
      
      // extract 3d points
      Eigen::Vector3d env_pt(closest_env_point.x, closest_env_point.y, closest_env_point.z);
      Eigen::Vector3d link_pt(closest_link_point.x, closest_link_point.y, closest_link_point.z);
      
      // extract task intensity and direction
      Eigen::Vector3d diff = env_pt - link_pt;
      Eigen::Vector3d direction = (diff.norm() > 1e-6) ? diff.normalized() : Eigen::Vector3d::Zero();
      
      // fill task info
      task.point = link_pt;
      task.direction = direction;
      task.distance = std::sqrt(min_dist_sq); 
      task.link_name = link_name;
      
      tasks.push_back(task);
    }
  }
  
  return tasks;
}

// tasks visualization
void ProximityTaskGenerator::publishProximityMarkers(const std::vector<ProximityTask> & tasks,
                             const rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr & marker_pub,
                             const std::string & frame_id, const rclcpp::Time & stamp)
{
  visualization_msgs::msg::MarkerArray marker_array;
  int id = 0;
  for (const auto & task : tasks)
  { 
    // hide tasks from joints not needed 
    double hide_tsk;
    if(task.link_name == "kuka_base_link" || task.link_name == "base_link" || task.link_name == "kuka_link_1"){
      hide_tsk = 0.0;
    }else{
      hide_tsk = 1.0;
    }

    // sphere marker for the minimum distance point
    visualization_msgs::msg::Marker sphere;
    sphere.header.frame_id = frame_id;
    sphere.header.stamp = stamp;
    sphere.ns = "proximity_points";
    sphere.id = id++;
    sphere.type = visualization_msgs::msg::Marker::SPHERE;
    sphere.action = visualization_msgs::msg::Marker::ADD;
    sphere.pose.position.x = task.point.x();
    sphere.pose.position.y = task.point.y();
    sphere.pose.position.z = task.point.z();
    sphere.pose.orientation.w = 1.0;
    sphere.scale.x = 0.05;  
    sphere.scale.y = 0.05;
    sphere.scale.z = 0.05;
    sphere.color.r = 0.3;
    sphere.color.g = 0.42;
    sphere.color.b = 0.66;
    sphere.color.a = 1.0*hide_tsk;
    marker_array.markers.push_back(sphere);

    // arrow marker for task direction
    visualization_msgs::msg::Marker arrow;
    arrow.header.frame_id = frame_id;
    arrow.header.stamp = stamp;
    arrow.ns = "proximity_direction";
    arrow.id = id++;
    arrow.type = visualization_msgs::msg::Marker::ARROW;
    arrow.action = visualization_msgs::msg::Marker::ADD;
    geometry_msgs::msg::Point start;
    start.x = task.point.x();
    start.y = task.point.y();
    start.z = task.point.z();
    double arrow_length = task.distance;
    geometry_msgs::msg::Point end;
    end.x = task.point.x() + task.direction.x() * arrow_length;
    end.y = task.point.y() + task.direction.y() * arrow_length;
    end.z = task.point.z() + task.direction.z() * arrow_length;
    arrow.points.push_back(start);
    arrow.points.push_back(end);
    arrow.scale.x = 0.02; 
    arrow.scale.y = 0.04; 
    arrow.scale.z = 0.1;  
    arrow.color.r = 0.3;
    arrow.color.g = 0.42;
    arrow.color.b = 0.66;
    arrow.color.a = 0.4*hide_tsk;
    marker_array.markers.push_back(arrow);
  }
  
  marker_pub->publish(marker_array);
}

// tasks for controller 
void ProximityTaskGenerator::publishProximityTasks(const std::vector<ProximityTask> & tasks,
                                  const rclcpp::Publisher<uc1_robot_perception::msg::ProximityTaskArray>::SharedPtr & task_pub)
{
  uc1_robot_perception::msg::ProximityTaskArray msg;

  for (const auto & task : tasks)
  {
    uc1_robot_perception::msg::ProximityTask task_msg;

    task_msg.min_point_robot.x = task.point.x();
    task_msg.min_point_robot.y = task.point.y();
    task_msg.min_point_robot.z = task.point.z();
    
    task_msg.min_point_vector.x = task.direction.x();
    task_msg.min_point_vector.y = task.direction.y();
    task_msg.min_point_vector.z = task.direction.z();
    
    task_msg.distance = task.distance;
    task_msg.link_id = task.link_name;
    
    msg.proximity_tasks.push_back(task_msg);
  }
  
  task_pub->publish(msg);
}

