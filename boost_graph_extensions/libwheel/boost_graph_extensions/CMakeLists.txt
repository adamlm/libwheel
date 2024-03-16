include(libwheel_target_set_install_rules)

add_library(libwheel_boost_graph_extensions INTERFACE)
add_library(libwheel::boost_graph_extensions ALIAS libwheel_boost_graph_extensions)

target_include_directories(libwheel_boost_graph_extensions
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/boost_graph_extensions>
)

target_link_libraries(libwheel_boost_graph_extensions
  INTERFACE
    Boost::graph
)

target_compile_features(libwheel_boost_graph_extensions
  INTERFACE
    cxx_std_20
)

libwheel_target_set_install_rules(libwheel_boost_graph_extensions)
