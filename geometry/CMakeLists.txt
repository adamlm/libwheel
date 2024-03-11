include(options.cmake)

add_subdirectory(libwheel/geometry)

if(libwheel_geometry_BUILD_TESTS)
  add_subdirectory(test)
endif()

if(libwheel_geometry_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
