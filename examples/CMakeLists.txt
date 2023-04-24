add_executable(rrt rrt.cpp)

target_include_directories(rrt
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(rrt
  PRIVATE
    libwheel::motion_planning
)
