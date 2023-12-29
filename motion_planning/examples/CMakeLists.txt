add_executable(rrt_simple rrt_simple.cpp)

target_include_directories(rrt_simple
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(rrt_simple
  PRIVATE
    libwheel::motion_planning
    fmt::fmt
)

target_compile_features(rrt_simple
  PRIVATE
    cxx_std_20
)

libwheel_target_set_compiler_warnings(rrt_simple
  PRIVATE
  WARNINGS_AS_ERRORS
)

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
