include(${PROJECT_SOURCE_DIR}/cmake/compiler_warnings.cmake)

add_executable(rrt rrt.cpp)

target_include_directories(rrt
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(rrt
  PRIVATE
    libwheel::motion_planning
)

wheel_cmake_target_compiler_warnings(rrt)

add_executable(custom_space custom_space.cpp)

target_include_directories(custom_space
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(custom_space
  PRIVATE
    libwheel::motion_planning
)

wheel_cmake_target_compiler_warnings(custom_space)
