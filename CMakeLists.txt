cmake_minimum_required(VERSION 3.22)
project(wheel_metaprogramming)
enable_testing()

option(wheel_metaprogramming_ENABLE_TESTING "Enable unit test for Wheel.Metaprogramming" ${PROJECT_IS_TOP_LEVEL})
option(wheel_metaprogramming_BUILD_EXAMPLES "Build examples for Wheel.Metaprogramming" ${PROJECT_IS_TOP_LEVEL})
option(wheel_metaprogramming_EXPORT_COMPILE_COMMANDS "Export compile commands for Wheel.Metaprogramming" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ${wheel_metaprogramming_EXPORT_COMPILE_COMMANDS})

add_subdirectory(libwheel/metaprogramming)

if(wheel_metaprogramming_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()
