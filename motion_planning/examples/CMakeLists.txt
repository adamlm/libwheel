include(${PROJECT_SOURCE_DIR}/cmake/compiler_warnings.cmake)

add_subdirectory(custom_vector_type)

add_executable(rrt rrt.cpp)

target_include_directories(rrt
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(rrt
  PRIVATE
    libwheel::motion_planning
    Eigen3::Eigen
)

wheel_cmake_target_compiler_warnings(rrt)
