include(libwheel_target_set_install_rules)

add_library(libwheel_motion_planning INTERFACE)
add_library(libwheel::motion_planning ALIAS libwheel_motion_planning)

target_include_directories(libwheel_motion_planning
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/motion_planning>
)

target_link_libraries(libwheel_motion_planning
  INTERFACE
    Boost::graph
    libwheel::metaprogramming
    range-v3::range-v3
)

target_compile_features(libwheel_motion_planning
  INTERFACE
    cxx_std_20
)

libwheel_target_set_install_rules(libwheel_motion_planning)
