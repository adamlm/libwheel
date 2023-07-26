add_subdirectory(libwheel/angle)

if(wheel_angle_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()
