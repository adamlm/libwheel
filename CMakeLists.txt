cmake_minimum_required(VERSION 3.22)
project(wheel_motion_planning)
enable_testing()

option(wheel_motion_planning_ENABLE_TESTING "Enable unit test for Wheel.Motion Planning" ${PROJECT_IS_TOP_LEVEL})
option(wheel_motion_planning_BUILD_EXAMPLES "Build examples for Wheel.Motion Planning" ${PROJECT_IS_TOP_LEVEL})
option(wheel_motion_planning_EXPORT_COMPILE_COMMANDS "Export compile commands for Wheel.Motion Planning" ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ${wheel_motion_planning_EXPORT_COMPILE_COMMANDS})

include(dependencies.cmake)

add_subdirectory(libwheel/motion_planning)

if(wheel_motion_planning_ENABLE_TESTING OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()

if(wheel_motion_planning_BUILD_EXAMPLES OR PROJECT_IS_TOP_LEVEL)
  add_subdirectory(examples)
endif()
