cmake_minimum_required(VERSION 3.8)
project(pointcloud_interactive_markers)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

cmake_policy(SET CMP0074 NEW)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(interactive_markers REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(orocos_kdl REQUIRED)
find_package(kdl_parser REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(urdf REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(pcl_msgs REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(PCL REQUIRED COMPONENTS io)


include_directories(
  include
  ${EIGEN3_INCLUDE_DIR}
)

add_executable(interactive-target src/interactive-target.cpp)
ament_target_dependencies(interactive-target 
rclcpp 
example_interfaces
sensor_msgs
geometry_msgs
orocos_kdl
kdl_parser
interactive_markers
visualization_msgs
tf2_geometry_msgs
tf2
tf2_ros
Eigen3
urdf
)

add_executable(mindist-dummy-broadcaster src/mindist-dummy-broadcaster.cpp)
ament_target_dependencies(mindist-dummy-broadcaster
    rclcpp
    tf2
    tf2_ros
    geometry_msgs
)

add_executable(sphere-cloud-broadcaster src/sphere-cloud.cpp)
ament_target_dependencies(sphere-cloud-broadcaster
    rclcpp
    tf2
    tf2_ros
    geometry_msgs
    sensor_msgs
    PCL
    Eigen3
    pcl_conversions
    tf2_eigen
    tf2_geometry_msgs
)

add_executable(cylinder-cloud-broadcaster src/cylinder-cloud.cpp)
ament_target_dependencies(cylinder-cloud-broadcaster
    rclcpp
    tf2
    tf2_ros
    geometry_msgs
    sensor_msgs
    PCL
    Eigen3
    pcl_conversions
    tf2_eigen
    tf2_geometry_msgs
)

add_executable(cylinder-cloud-broadcaster-multi src/cylinder-cloud-multi.cpp)
ament_target_dependencies(cylinder-cloud-broadcaster-multi
    rclcpp
    tf2
    tf2_ros
    geometry_msgs
    sensor_msgs
    PCL
    Eigen3
    pcl_conversions
    tf2_eigen
    tf2_geometry_msgs
)

add_executable(chassis-cloud src/chassis-cloud.cpp)
ament_target_dependencies(chassis-cloud
    rclcpp
    tf2
    tf2_ros
    geometry_msgs
    sensor_msgs
    PCL
    Eigen3
    pcl_conversions
    tf2_eigen
    tf2_geometry_msgs
)

add_executable(obstacle-cloud-broadcaster src/obstacle_cloud_broadcaster.cpp)
ament_target_dependencies(obstacle-cloud-broadcaster
    rclcpp
    tf2
    tf2_ros
    geometry_msgs
    sensor_msgs
    PCL
    Eigen3
    pcl_conversions
    tf2_eigen
    tf2_geometry_msgs
)

install(TARGETS 
interactive-target
mindist-dummy-broadcaster
sphere-cloud-broadcaster
cylinder-cloud-broadcaster
cylinder-cloud-broadcaster-multi
chassis-cloud
obstacle-cloud-broadcaster
DESTINATION lib/${PROJECT_NAME}
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
