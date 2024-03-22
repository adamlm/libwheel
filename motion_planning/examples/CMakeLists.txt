add_executable(rrt_max_distance rrt_max_distance.cpp)

target_include_directories(rrt_max_distance
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(rrt_max_distance
  PRIVATE
    libwheel::motion_planning
    fmt::fmt
)

target_compile_features(rrt_max_distance
  PRIVATE
    cxx_std_20
)

libwheel_target_set_compiler_warnings(rrt_max_distance
  PRIVATE
  WARNINGS_AS_ERRORS
)

add_executable(rrt_max_distance_holes rrt_max_distance_holes.cpp)

target_include_directories(rrt_max_distance_holes
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(rrt_max_distance_holes
  PRIVATE
    libwheel::motion_planning
    fmt::fmt
)

target_compile_features(rrt_max_distance_holes
  PRIVATE
    cxx_std_20
)

libwheel_target_set_compiler_warnings(rrt_max_distance_holes
  PRIVATE
  WARNINGS_AS_ERRORS
)
