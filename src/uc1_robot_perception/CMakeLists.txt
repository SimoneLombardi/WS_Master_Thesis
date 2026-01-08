cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")
project(uc1_robot_perception)

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


rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/ProximityTask.msg"
  "msg/ProximityTaskArray.msg"
  "msg/Contact.msg"
  "msg/ContactArray.msg"
  DEPENDENCIES geometry_msgs std_msgs
)

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

# fake skin data publisher
add_executable(simulated_contact_publisher src/SimulatedContactPublisher.cpp)
ament_target_dependencies(simulated_contact_publisher 
                          rclcpp 
                          geometry_msgs )
rosidl_target_interfaces(simulated_contact_publisher
              ${PROJECT_NAME} "rosidl_typesupport_cpp")

# interactive skin data publisher
add_executable(interactive_contact_publisher src/InteractiveContactPublisher.cpp)
ament_target_dependencies(interactive_contact_publisher 
                            rclcpp 
                            geometry_msgs 
                            sensor_msgs
                            tf2
                            tf2_ros
                            PCL
                            Eigen3
                            pcl_conversions
                            tf2_eigen
                            tf2_geometry_msgs
                            visualization_msgs)
rosidl_target_interfaces(interactive_contact_publisher
              ${PROJECT_NAME} "rosidl_typesupport_cpp")

# proximity task generator
add_executable(proximity_task_generator src/ProximityTest.cpp src/ProximityTaskGenerator.cpp)
ament_target_dependencies(proximity_task_generator 
                          rclcpp 
                          geometry_msgs 
                          sensor_msgs
                          tf2
                          tf2_ros
                          PCL
                          Eigen3
                          pcl_conversions
                          tf2_eigen
                          tf2_geometry_msgs
                          visualization_msgs)
rosidl_target_interfaces(proximity_task_generator
              ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS
  simulated_contact_publisher
  interactive_contact_publisher
  proximity_task_generator
  DESTINATION lib/${PROJECT_NAME})

# Install launch files
install(DIRECTORY
  DESTINATION share/${PROJECT_NAME}/
)

# Install robot model files
install(DIRECTORY
  resources
  DESTINATION share/${PROJECT_NAME}/
)

# Install message files
install(
  DIRECTORY msg
  DESTINATION share/${PROJECT_NAME}
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
