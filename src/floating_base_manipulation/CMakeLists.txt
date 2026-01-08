cmake_minimum_required(VERSION 3.8)
project(floating_base_manipulation)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
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
find_package(tf2_geometry_msgs REQUIRED)
find_package(orocos_kdl REQUIRED)
find_package(kdl_parser REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(urdf REQUIRED)

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
urdf)

add_executable(static-target src/static-target.cpp)
ament_target_dependencies(static-target 
rclcpp 
example_interfaces
sensor_msgs
geometry_msgs
kdl_parser
visualization_msgs
tf2_geometry_msgs
tf2
tf2_ros
Eigen3
urdf)


install(TARGETS 
interactive-target
static-target
DESTINATION lib/${PROJECT_NAME}
)

# Install launch files.
install(DIRECTORY
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
