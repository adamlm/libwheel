include(options.cmake)

if(NOT libwheel_strongly_typed_matrix_BUILD_LIB)
  return()
endif()

add_subdirectory(libwheel/strongly_typed_matrix)

if(wheel_strongly_typed_matrix_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()
