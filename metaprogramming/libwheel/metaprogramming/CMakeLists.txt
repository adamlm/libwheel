include(libwheel_target_set_install_rules)

add_library(libwheel_metaprogramming INTERFACE)
add_library(libwheel::metaprogramming ALIAS libwheel_metaprogramming)

target_include_directories(libwheel_metaprogramming
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/metaprogramming>
)

target_compile_features(libwheel_metaprogramming
  INTERFACE
    cxx_std_20
)

libwheel_target_set_install_rules(libwheel_metaprogramming)
