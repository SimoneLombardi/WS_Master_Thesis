# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_uc1_robot_controllers_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED uc1_robot_controllers_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(uc1_robot_controllers_FOUND FALSE)
  elseif(NOT uc1_robot_controllers_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(uc1_robot_controllers_FOUND FALSE)
  endif()
  return()
endif()
set(_uc1_robot_controllers_CONFIG_INCLUDED TRUE)

# output package information
if(NOT uc1_robot_controllers_FIND_QUIETLY)
  message(STATUS "Found uc1_robot_controllers: 0.0.0 (${uc1_robot_controllers_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'uc1_robot_controllers' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${uc1_robot_controllers_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(uc1_robot_controllers_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${uc1_robot_controllers_DIR}/${_extra}")
endforeach()
