include(options.cmake)

if(NOT libwheel_metaprogramming_BUILD_LIB)
  return()
endif()

add_subdirectory(libwheel/metaprogramming)

if(libwheel_metaprogramming_BUILD_TESTS)
  add_subdirectory(test)
endif()
