include(options.cmake)

add_subdirectory(libwheel/angle)

if(libwheel_angle_BUILD_TESTS)
  add_subdirectory(test)
endif()
