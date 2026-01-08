cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")
project(environment_pointcloud_processing)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_compile_options(-Wall -Wextra)
endif()

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
find_package(pcl_conversions REQUIRED)
find_package(pcl_msgs REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(urdf REQUIRED)
find_package(Doxygen)
find_package(PCL REQUIRED COMPONENTS io)

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxygen)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
endif()

include_directories(
  include
  /opt/ros/humble/include
  ${EIGEN3_INCLUDE_DIR}
)

# -------------------------------------------- test main for admittance control
# env cloud publisher
add_executable(env_cloud_manager src/EnvCloudMain.cpp src/EnvCloudManager.cpp)
ament_target_dependencies(env_cloud_manager
  rclcpp
  sensor_msgs
  pcl_conversions
  tf2
  tf2_ros
)
target_link_libraries(env_cloud_manager
  ${PCL_LIBRARIES}
)

# motion extraction node
add_executable(cloud_motion_segmentation src/MotionCloudSegmentation.cpp src/CloudMotionExtractor.cpp)
ament_target_dependencies(cloud_motion_segmentation
  rclcpp
  sensor_msgs
  pcl_conversions
  tf2
  tf2_ros
)
target_link_libraries(cloud_motion_segmentation
  ${PCL_LIBRARIES}
)


install(TARGETS 
env_cloud_manager
cloud_motion_segmentation
DESTINATION lib/${PROJECT_NAME}
)

# Install launch files.
install(DIRECTORY
  resources
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
