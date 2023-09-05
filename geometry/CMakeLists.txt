include(options.cmake)

if(NOT libwheel_geometry_BUILD_LIB)
  return()
endif()

add_subdirectory(libwheel/geometry)

if(libwheel_geometry_BUILD_TESTS)
  add_subdirectory(test)
endif()

if(libwheel_geometry_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
