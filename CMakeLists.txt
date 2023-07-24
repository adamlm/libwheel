# Dependencies acquired using FetchContent need to have the SYSTEM target
# property---added in CMake 3.25---set to TRUE. Otherwise, the compiler warnings
# will complain about issues in third-party libraries.
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(wheel_geometry)
enable_testing()

option(wheel_geometry_ENABLE_TESTING "Enable unit tests" ${PROJECT_IS_TOP_LEVEL})
option(wheel_geometry_BUILD_EXAMPES "Build examples" ${PROJECT_IS_TOP_LEVEL})
option(wheel_geometry_EXPORT_COMPILE_COMMANDS "Export compile commands" TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ${wheel_geometry_EXPORT_COMPILE_COMMANDS})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(dependencies.cmake)

add_subdirectory(libwheel/geometry)

if(wheel_geometry_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()

if(wheel_geometry_BUILD_EXAMPES OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(examples)
endif()
