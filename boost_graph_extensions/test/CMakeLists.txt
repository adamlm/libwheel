add_executable(libwheel_boost_graph_extensions_tests
  test_visitors.cpp
)

target_link_libraries(libwheel_boost_graph_extensions_tests
  PRIVATE
    libwheel::boost_graph_extensions
    GTest::gtest_main
)

libwheel_target_set_compiler_warnings(libwheel_boost_graph_extensions_tests
  PRIVATE
  COMPILE_WARNING_AS_ERROR TRUE
)

include(GoogleTest)
gtest_discover_tests(libwheel_boost_graph_extensions_tests)
