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

if(libwheel_BUILD_ANGLE)
  add_subdirectory(angle)
endif()

add_subdirectory(geometry)

if(libwheel_BUILD_METAPROGRAMMING)
  add_subdirectory(metaprogramming)
endif()

if(libwheel_BUILD_MOTION_PLANNING)
  add_subdirectory(motion_planning)
endif()

if(libwheel_BUILD_STRONGLY_TYPED_MATRIX)
  add_subdirectory(strongly_typed_matrix)
endif()

if(libwheel_bounded_value_BUILD_LIB)
  add_subdirectory(bounded_value)
endif()
