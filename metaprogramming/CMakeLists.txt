include(options.cmake)

add_subdirectory(libwheel/metaprogramming)

if(libwheel_metaprogramming_BUILD_TESTS)
  add_subdirectory(test)
endif()
