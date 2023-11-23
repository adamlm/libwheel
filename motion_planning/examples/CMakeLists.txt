add_executable(rapidly_exploring_random_trees rapidly_exploring_random_trees.cpp)

target_include_directories(rapidly_exploring_random_trees
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(rapidly_exploring_random_trees
  PRIVATE
    libwheel::motion_planning
    fmt::fmt
)

target_compile_features(rapidly_exploring_random_trees
  PRIVATE
    cxx_std_20
)

libwheel_target_set_compiler_warnings(rapidly_exploring_random_trees
  PRIVATE
  WARNINGS_AS_ERRORS
)
