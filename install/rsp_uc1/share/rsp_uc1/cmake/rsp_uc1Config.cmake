# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_rsp_uc1_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED rsp_uc1_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(rsp_uc1_FOUND FALSE)
  elseif(NOT rsp_uc1_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(rsp_uc1_FOUND FALSE)
  endif()
  return()
endif()
set(_rsp_uc1_CONFIG_INCLUDED TRUE)

# output package information
if(NOT rsp_uc1_FIND_QUIETLY)
  message(STATUS "Found rsp_uc1: 3.0.3 (${rsp_uc1_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'rsp_uc1' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${rsp_uc1_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(rsp_uc1_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_targets-extras.cmake;ament_cmake_export_dependencies-extras.cmake")
foreach(_extra ${_extras})
  include("${rsp_uc1_DIR}/${_extra}")
endforeach()
