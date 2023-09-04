include(options.cmake)

if(NOT libwheel_angle_BUILD_LIB)
  return()
endif()

add_subdirectory(libwheel/angle)

if(libwheel_angle_BUILD_TESTS)
  add_subdirectory(test)
endif()
