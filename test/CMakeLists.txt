include(GoogleTest)

add_executable(test_vector
  test_vector.cpp
)

target_link_libraries(test_vector
  PRIVATE
    libwheel::motion_planning
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(test_vector)
