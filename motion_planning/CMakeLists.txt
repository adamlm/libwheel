include(options.cmake)

add_subdirectory(libwheel/motion_planning)

if(wheel_motion_planning_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()

add_subdirectory(examples)
