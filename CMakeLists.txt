# Dependencies acquired using FetchContent need to have the SYSTEM target
# property---added in CMake 3.25---set to TRUE. Otherwise, the compiler warnings
# will complain about issues in third-party libraries.
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(libwheel)
enable_testing()

option(libwheel_EXPORT_COMPILE_COMMANDS "Export compile commands" ${PROJECT_IS_TOP_LEVEL})

option(libwheel_BUILD_ANGLE "Build the Wheel Angle library" ON)
option(libwheel_BUILD_GEOMETRY "Build the Wheel Geometry library" ON)
option(libwheel_BUILD_METAPROGRAMMING "Build the Wheel Metaprogramming library" ON)
option(libwheel_BUILD_MOTION_PLANNING "Build the Wheel Motion Planning library" ON)
option(libwheel_BUILD_STRONGLY_TYPED_MATRIX "Build the Wheel Strongly-Typed Matrix library" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(dependencies.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ${libwheel_EXPORT_COMPILE_COMMANDS})

if(libwheel_BUILD_ANGLE)
  add_subdirectory(angle)
endif()

if(libwheel_BUILD_GEOMETRY)
  add_subdirectory(geometry)
endif()

if(libwheel_BUILD_METAPROGRAMMING)
  add_subdirectory(metaprogramming)
endif()

if(libwheel_BUILD_MOTION_PLANNING)
  # add_subdirectory(motion_planning)
endif()

if(libwheel_BUILD_STRONGLY_TYPED_MATRIX)
  add_subdirectory(strongly_typed_matrix)
endif()
