include(libwheel_target_set_install_rules)

add_library(libwheel_geometry INTERFACE)
add_library(libwheel::geometry ALIAS libwheel_geometry)

target_include_directories(libwheel_geometry
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/geometry>
)

target_link_libraries(libwheel_geometry
  INTERFACE
    Eigen3::Eigen
    range-v3::range-v3
)

target_compile_features(libwheel_geometry
  INTERFACE
    cxx_std_20
)

libwheel_target_set_install_rules(libwheel_geometry)
