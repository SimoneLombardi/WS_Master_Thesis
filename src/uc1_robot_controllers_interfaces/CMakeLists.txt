cmake_minimum_required(VERSION 3.8)
project(uc1_robot_controllers_interfaces)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(message_filters REQUIRED)
find_package(sensor_msgs REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "action/MoveRobot.action"
  "action/MoveRobotTP.action"
  "msg/MoveRobotPoint.msg"
  "msg/MoveRobotOrient.msg"
  "msg/MoveRobotGoal.msg"
  DEPENDENCIES geometry_msgs std_msgs 
)

ament_export_dependencies(rosidl_default_runtime)

# library stuff
add_library(TPComputation src/TPComputation.cpp)
add_library(LowPassFilter src/LowPassFilter.cpp)

target_include_directories(TPComputation
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/uc1_robot_controllers_interfaces>
    $<INSTALL_INTERFACE:include>
    ${EIGEN_INCLUDE_DIRS}
)

target_include_directories(LowPassFilter
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/uc1_robot_controllers_interfaces>
    $<INSTALL_INTERFACE:include>
    ${EIGEN_INCLUDE_DIRS}
)


target_link_libraries(TPComputation
  Eigen3::Eigen
)

target_link_libraries(LowPassFilter
  Eigen3::Eigen
)

ament_export_targets(TPComputation HAS_LIBRARY_TARGET)
ament_export_targets(LowPassFilter HAS_LIBRARY_TARGET)
ament_export_dependencies(Eigen3)

install(
  DIRECTORY include/uc1_robot_controllers_interfaces
  DESTINATION include
)

install(
  TARGETS TPComputation 
  EXPORT TPComputation 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(
  TARGETS LowPassFilter 
  EXPORT LowPassFilter 
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)


add_executable(sync_joint_topic_exe src/sync_jst.cpp) # Joint State Topic
ament_target_dependencies(sync_joint_topic_exe
  sensor_msgs
  message_filters
)

install(TARGETS
  sync_joint_topic_exe
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
