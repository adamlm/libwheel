include(GoogleTest)

add_executable(unit_tests
  test_vector.cpp
  test_space.cpp
)

target_link_libraries(unit_tests
  PRIVATE
    libwheel::motion_planning
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(unit_tests)
