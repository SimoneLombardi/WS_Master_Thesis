cmake_minimum_required(VERSION 3.8)
project(keyboard_publisher_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(keyboard_publisher_node src/keyboard_publisher.cpp)
ament_target_dependencies(keyboard_publisher_node rclcpp std_msgs SDL2)

target_include_directories(keyboard_publisher_node PRIVATE
  ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(keyboard_publisher_node
  ${SDL2_LIBRARIES}
)

install(TARGETS keyboard_publisher_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
