cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")
project(uc1_robot_controllers)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_compile_options(-Wall -Wextra)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(interactive_markers REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_eigen REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(orocos_kdl REQUIRED)
find_package(kdl_parser REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(pcl_msgs REQUIRED)
find_package(pcl_ros REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(urdf REQUIRED)
find_package(Doxygen)
#find_package(skin REQUIRED)
find_package(PCL REQUIRED COMPONENTS io)

# custom msgs
find_package(rosidl_default_generators REQUIRED)
find_package(rosidl_default_runtime REQUIRED)
find_package(uc1_robot_perception REQUIRED)

# my pkgs find
find_package(uc1_robot_controllers_interfaces REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)

#rosidl_generate_interfaces(${PROJECT_NAME}
#  "msg/ProximityTask.msg"
#  "msg/ProximityTaskArray.msg"
#  "msg/Contact.msg"
#  "msg/ContactArray.msg"
#  DEPENDENCIES geometry_msgs std_msgs
#)

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


# add_executable(ur10e-test-controller src/UR10eTestController.cpp src/UR10eRobot.cpp src/TfGoalBroadcaster.cpp)
# ament_target_dependencies(ur10e-test-controller 
# rclcpp 
# example_interfaces
# sensor_msgs
# geometry_msgs
# visualization_msgs
# orocos_kdl
# kdl_parser
# tf2
# tf2_ros
# Eigen3
# urdf
# #skin
# uc1_robot_perception
# uc1_robot_controllers_interfaces
# rclcpp_action
# rclcpp_components
# )

# add_executable(ur10e-proximity-controller src/UR10eProximityController.cpp src/UR10eRobot.cpp src/TfGoalBroadcaster.cpp)
# ament_target_dependencies(ur10e-proximity-controller 
# rclcpp 
# example_interfaces
# sensor_msgs
# geometry_msgs
# visualization_msgs
# orocos_kdl
# kdl_parser
# tf2
# tf2_ros
# Eigen3
# urdf
# #skin
# uc1_robot_perception
# uc1_robot_controllers_interfaces
# rclcpp_action
# rclcpp_components
# )

# add_executable(ur10e-tactile-controller src/UR10eTactileController.cpp src/UR10eRobot.cpp src/TfGoalBroadcaster.cpp)
# ament_target_dependencies(ur10e-tactile-controller 
# rclcpp 
# example_interfaces
# sensor_msgs
# geometry_msgs
# visualization_msgs
# orocos_kdl
# kdl_parser
# tf2
# tf2_ros
# Eigen3
# urdf
# #skin
# uc1_robot_perception
# uc1_robot_controllers_interfaces
# rclcpp_action
# rclcpp_components
# )

# add_executable(kuka-test-controller src/KukaTestController.cpp src/KukaRobot.cpp src/TfGoalBroadcaster.cpp)
# ament_target_dependencies(kuka-test-controller 
# rclcpp 
# example_interfaces
# sensor_msgs
# std_msgs
# geometry_msgs
# visualization_msgs
# orocos_kdl
# kdl_parser
# tf2
# tf2_ros
# Eigen3
# urdf
# uc1_robot_controllers_interfaces
# rclcpp_action
# rclcpp_components
# )



add_executable(kuka-joint-cmd-buf src/KukaJointCommandBuffer.cpp)
ament_target_dependencies(kuka-joint-cmd-buf
rclcpp 
std_msgs
example_interfaces
sensor_msgs
geometry_msgs
uc1_robot_controllers_interfaces
rclcpp_action
rclcpp_components
)


# add_executable(uc1_mission src/uc1_mission_main.cpp src/KukaRobot.cpp src/UR10eRobot.cpp src/TfGoalBroadcaster.cpp src/MissionManager.cpp)
# ament_target_dependencies(uc1_mission 
# rclcpp 
# example_interfaces
# sensor_msgs
# std_msgs
# geometry_msgs
# visualization_msgs
# orocos_kdl
# kdl_parser
# tf2
# tf2_ros
# Eigen3
# urdf
# uc1_robot_perception
# uc1_robot_controllers_interfaces
# rclcpp_action
# rclcpp_components
# )


#add_executable(joint-jacobian-pub src/joint_controller/joint_jacobian_pub.cpp src/KukaRobot.cpp src/UR10eRobot.cpp)
# ament_target_dependencies(joint-jacobian-pub
# rclcpp 
# example_interfaces
# sensor_msgs
# std_msgs
# geometry_msgs
# visualization_msgs
# orocos_kdl
# kdl_parser
# tf2
# tf2_ros
# Eigen3
# urdf
# uc1_robot_perception
# )

# add_executable(joint-jacobian-pub-2 src/joint_controller/joint_jacobian_pub_2.cpp src/KukaRobot.cpp src/UR10eRobot.cpp)
# ament_target_dependencies(joint-jacobian-pub-2
# rclcpp 
# example_interfaces
# sensor_msgs
# std_msgs
# geometry_msgs
# visualization_msgs
# orocos_kdl
# kdl_parser
# tf2
# tf2_ros
# Eigen3
# urdf
# uc1_robot_perception
# )

# add_executable(joint-jacobian-pub-3 src/joint_controller/joint_jacobian_pub_3.cpp src/KukaRobot.cpp src/UR10eRobot.cpp)
# ament_target_dependencies(joint-jacobian-pub-3
# rclcpp 
# example_interfaces
# sensor_msgs
# std_msgs
# geometry_msgs
# visualization_msgs
# orocos_kdl
# kdl_parser
# tf2
# tf2_ros
# Eigen3
# urdf
# uc1_robot_perception
# )

add_executable(joint-robot-test src/joint_controller/joint_robot_test.cpp src/JointRobot.cpp src/KukaRobot.cpp src/UR10eRobot.cpp src/TfGoalBroadcaster.cpp)
target_link_libraries(joint-robot-test
  uc1_robot_controllers_interfaces::TPComputation
)
ament_target_dependencies(joint-robot-test
rclcpp 
example_interfaces
sensor_msgs
std_msgs
geometry_msgs
visualization_msgs
orocos_kdl
kdl_parser
tf2
tf2_ros
Eigen3
urdf
uc1_robot_perception
uc1_robot_controllers_interfaces
rclcpp_action
rclcpp_components
)

add_executable(joint-robot-tp-test src/joint_controller/joint_robot_tp_test.cpp 
  src/JointRobotTP/JointRobotTP.cpp 
  src/JointRobotTP/JointRobotTP_functions.cpp
  src/KukaRobot.cpp 
  src/UR10eRobot.cpp 
  src/TfGoalBroadcaster.cpp 
)
target_link_libraries(joint-robot-tp-test
  uc1_robot_controllers_interfaces::TPComputation
)
ament_target_dependencies(joint-robot-tp-test
rclcpp 
example_interfaces
sensor_msgs
std_msgs
geometry_msgs
visualization_msgs
orocos_kdl
kdl_parser
tf2
tf2_ros
Eigen3
urdf
uc1_robot_perception
uc1_robot_controllers_interfaces
rclcpp_action
rclcpp_components
)

add_executable(robot-test src/joint_controller/test_robot_functions.cpp src/KukaRobot.cpp src/UR10eRobot.cpp src/TfGoalBroadcaster.cpp)
ament_target_dependencies(robot-test
rclcpp 
example_interfaces
sensor_msgs
std_msgs
geometry_msgs
visualization_msgs
orocos_kdl
kdl_parser
tf2
tf2_ros
Eigen3
urdf
uc1_robot_perception
uc1_robot_controllers_interfaces
rclcpp_action
rclcpp_components
)

install(TARGETS 
  #kuka-test-controller
  #ur10e-test-controller
  kuka-joint-cmd-buf
  #uc1_mission
  #ur10e-proximity-controller
  #ur10e-tactile-controller
  #joint-jacobian-pub
  #joint-jacobian-pub-2
  #joint-jacobian-pub-3
  joint-robot-test
  joint-robot-tp-test
  robot-test
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files.
install(DIRECTORY
  launch
  resources
  urdf
  msg
  config
  DESTINATION share/${PROJECT_NAME}/
)

# Install package.xml (required for custom msgs)
install(
  FILES package.xml
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
