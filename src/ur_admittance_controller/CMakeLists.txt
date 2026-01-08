cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")
project(ur_admittance_controller)

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



# add_executable(ur10e-test-controller src/UR10eTestController.cpp 
#                 src/UR10eRobot.cpp 
#                 src/ProximityPerceptionNetwork.cpp
#                 ${SOURCES}
#                 )
# ament_target_dependencies(ur10e-test-controller 
# rclcpp 
# example_interfaces
# sensor_msgs
# geometry_msgs
# orocos_kdl
# kdl_parser
# tf2
# tf2_ros
# Eigen3
# urdf
# skin)

# -------------------------------------------- test main for admittance control
add_executable(ur10e-test-admittance src/UR10eTestAdmittance.cpp 
                src/UR10eRobot.cpp 
                )
ament_target_dependencies(ur10e-test-admittance 
rclcpp 
pcl_conversions
example_interfaces
sensor_msgs
geometry_msgs
orocos_kdl
kdl_parser
tf2
tf2_ros
tf2_geometry_msgs
tf2_eigen
Eigen3
urdf
#skin
) 

add_executable(kuka-test-controller src/KukaTestController.cpp src/KukaRobot.cpp)
ament_target_dependencies(kuka-test-controller 
rclcpp 
example_interfaces
sensor_msgs
geometry_msgs
orocos_kdl
kdl_parser
tf2
tf2_ros
Eigen3
urdf)



install(TARGETS 
kuka-test-controller
ur10e-test-admittance
DESTINATION lib/${PROJECT_NAME}
)

# Install launch files.
install(DIRECTORY
  launch
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
