add_executable(libwheel_motion_planning_tests
  test_space.cpp
  test_type_traits.cpp
  test_make_vector.cpp
  test_orthotope.cpp
)

target_link_libraries(libwheel_motion_planning_tests
  PRIVATE
    libwheel::motion_planning
    GTest::gtest
    GTest::gtest_main
)

libwheel_target_set_compiler_warnings(libwheel_motion_planning_tests
  PRIVATE
  COMPILE_WARNING_AS_ERROR TRUE
)

include(GoogleTest)
gtest_discover_tests(libwheel_motion_planning_tests)
