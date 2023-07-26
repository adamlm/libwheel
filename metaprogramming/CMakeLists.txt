add_subdirectory(libwheel/metaprogramming)

if(wheel_metaprogramming_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()
