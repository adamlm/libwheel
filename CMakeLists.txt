# Dependencies acquired using FetchContent need to have the SYSTEM target
# property---added in CMake 3.25---set to TRUE. Otherwise, the compiler warnings
# will complain about issues in third-party libraries.
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(libwheel)
enable_testing()

include(options.cmake)
include(dependencies.cmake)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ${libwheel_EXPORT_COMPILE_COMMANDS})

include(libwheel_conditionally_add_to_build)

libwheel_conditionally_add_to_build(angle libwheel_angle_BUILD_LIB)
libwheel_conditionally_add_to_build(geometry libwheel_geometry_BUILD_LIB)
libwheel_conditionally_add_to_build(metaprogramming libwheel_metaprogramming_BUILD_LIB)
libwheel_conditionally_add_to_build(motion_planning libwheel_motion_planning_BUILD_LIB)
libwheel_conditionally_add_to_build(strongly_typed_matrix libwheel_strongly_typed_matrix_BUILD_LIB)
