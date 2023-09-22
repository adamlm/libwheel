add_executable(struct_vector struct_vector.cpp)

target_include_directories(struct_vector
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
)

target_link_libraries(struct_vector
  PRIVATE
    libwheel::motion_planning
)

libwheel_target_set_compiler_warnings(struct_vector
  PRIVATE
  WARNINGS_AS_ERRORS
)


add_executable(strongly_typed_vector strongly_typed_vector.cpp)

target_link_libraries(strongly_typed_vector
  PRIVATE
    libwheel::motion_planning
    libwheel::strongly_typed_matrix
)

libwheel_target_set_compiler_warnings(strongly_typed_vector
  PRIVATE
  WARNINGS_AS_ERRORS
)


add_executable(eigen_vector eigen_vector.cpp)

target_compile_features(eigen_vector
  PRIVATE
    cxx_std_20
)

target_link_libraries(eigen_vector
  PRIVATE
    libwheel::motion_planning
    Eigen3::Eigen
)

libwheel_target_set_compiler_warnings(eigen_vector
  PRIVATE
  WARNINGS_AS_ERRORS
)
