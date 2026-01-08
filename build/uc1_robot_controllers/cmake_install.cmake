# Install script for directory: /home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/src/uc1_robot_controllers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/install/uc1_robot_controllers")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/kuka-joint-cmd-buf" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/kuka-joint-cmd-buf")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/kuka-joint-cmd-buf"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers" TYPE EXECUTABLE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/kuka-joint-cmd-buf")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/kuka-joint-cmd-buf" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/kuka-joint-cmd-buf")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/kuka-joint-cmd-buf"
         OLD_RPATH "/opt/ros/humble/lib:/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/install/uc1_robot_controllers_interfaces/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/kuka-joint-cmd-buf")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-test")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-test"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers" TYPE EXECUTABLE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/joint-robot-test")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-test")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-test"
         OLD_RPATH "/opt/ros/humble/lib:/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/install/uc1_robot_perception/lib:/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/install/uc1_robot_controllers_interfaces/lib:/opt/ros/humble/lib/x86_64-linux-gnu:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-test")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-tp-test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-tp-test")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-tp-test"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers" TYPE EXECUTABLE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/joint-robot-tp-test")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-tp-test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-tp-test")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-tp-test"
         OLD_RPATH "/opt/ros/humble/lib:/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/install/uc1_robot_perception/lib:/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/install/uc1_robot_controllers_interfaces/lib:/opt/ros/humble/lib/x86_64-linux-gnu:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/joint-robot-tp-test")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/robot-test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/robot-test")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/robot-test"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers" TYPE EXECUTABLE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/robot-test")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/robot-test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/robot-test")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/robot-test"
         OLD_RPATH "/opt/ros/humble/lib:/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/install/uc1_robot_perception/lib:/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/install/uc1_robot_controllers_interfaces/lib:/opt/ros/humble/lib/x86_64-linux-gnu:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/uc1_robot_controllers/robot-test")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers/" TYPE DIRECTORY FILES
    "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/src/uc1_robot_controllers/launch"
    "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/src/uc1_robot_controllers/resources"
    "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/src/uc1_robot_controllers/urdf"
    "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/src/uc1_robot_controllers/msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/src/uc1_robot_controllers/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/uc1_robot_controllers")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/uc1_robot_controllers")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers/environment" TYPE FILE FILES "/opt/ros/humble/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers/environment" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers/environment" TYPE FILE FILES "/opt/ros/humble/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers/environment" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_index/share/ament_index/resource_index/packages/uc1_robot_controllers")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers/cmake" TYPE FILE FILES
    "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_core/uc1_robot_controllersConfig.cmake"
    "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/ament_cmake_core/uc1_robot_controllersConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/uc1_robot_controllers" TYPE FILE FILES "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/src/uc1_robot_controllers/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/maclab/Documents/ROS_WORKSPACES/WS_Master_Thesis/build/uc1_robot_controllers/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
