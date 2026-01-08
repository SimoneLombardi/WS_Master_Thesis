#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "rsp_uc1::rsp_uc1_node" for configuration ""
set_property(TARGET rsp_uc1::rsp_uc1_node APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(rsp_uc1::rsp_uc1_node PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/librsp_uc1_node.so"
  IMPORTED_SONAME_NOCONFIG "librsp_uc1_node.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS rsp_uc1::rsp_uc1_node )
list(APPEND _IMPORT_CHECK_FILES_FOR_rsp_uc1::rsp_uc1_node "${_IMPORT_PREFIX}/lib/librsp_uc1_node.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
