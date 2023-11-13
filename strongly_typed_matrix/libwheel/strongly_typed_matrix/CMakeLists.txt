include(libwheel_target_set_install_rules)

add_library(libwheel_strongly_typed_matrix INTERFACE)
add_library(libwheel::strongly_typed_matrix ALIAS libwheel_strongly_typed_matrix)

target_include_directories(libwheel_strongly_typed_matrix
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/strongly_typed_matrix>
)

target_link_libraries(libwheel_strongly_typed_matrix
  INTERFACE
    libwheel::metaprogramming
    Eigen3::Eigen
)

target_compile_features(libwheel_strongly_typed_matrix
  INTERFACE
    cxx_std_20
)

libwheel_target_set_install_rules(libwheel_strongly_typed_matrix)
