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

libwheel_target_set_compiler_warnings(rrt
  PRIVATE
  WARNINGS_AS_ERRORS
)
