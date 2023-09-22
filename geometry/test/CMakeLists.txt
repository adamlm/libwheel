include(wheel_compiler_warnings)

add_executable(libwheel_geometry_unit_tests
  test_half_plane.cpp
  test_line.cpp
  test_linear_equation.cpp
  test_polygon.cpp
)

target_link_libraries(libwheel_geometry_unit_tests
  PRIVATE
    libwheel::geometry
    GTest::gtest
    GTest::gtest_main
)

libwheel_target_set_compiler_warnings(libwheel_geometry_unit_tests
  PRIVATE
  WARNINGS_AS_ERRORS
)

include(GoogleTest)
gtest_discover_tests(libwheel_geometry_unit_tests)
