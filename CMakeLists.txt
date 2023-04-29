cmake_minimum_required(VERSION 3.22)
project(wheel_angle VERSION 0.1.0)
enable_testing()

option(wheel_angle_ENABLE_TESTING "Enable unit test for Wheel.Angle" ${PROJECT_IS_TOP_LEVEL})
option(wheel_angle_BUILD_EXAMPLES "Build examples for Wheel.Angle" ${PROJECT_IS_TOP_LEVEL})
option(wheel_angle_EXPORT_COMPILE_COMMANDS "Export compile commands for Wheel.Angle" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ${wheel_angle_EXPORT_COMPILE_COMMANDS})

include(dependencies.cmake)

add_subdirectory(libwheel/angle)

if(wheel_angle_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()

if(wheel_angle_BUILD_EXAMPLES OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(examples)
endif()
