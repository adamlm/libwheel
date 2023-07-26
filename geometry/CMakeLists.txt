add_subdirectory(libwheel/geometry)

if(wheel_geometry_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()
