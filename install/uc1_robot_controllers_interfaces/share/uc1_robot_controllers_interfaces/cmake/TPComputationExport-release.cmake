#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "uc1_robot_controllers_interfaces::TPComputation" for configuration "Release"
set_property(TARGET uc1_robot_controllers_interfaces::TPComputation APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(uc1_robot_controllers_interfaces::TPComputation PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libTPComputation.so"
  IMPORTED_SONAME_RELEASE "libTPComputation.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS uc1_robot_controllers_interfaces::TPComputation )
list(APPEND _IMPORT_CHECK_FILES_FOR_uc1_robot_controllers_interfaces::TPComputation "${_IMPORT_PREFIX}/lib/libTPComputation.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
