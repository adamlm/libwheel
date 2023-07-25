include(GoogleTest)

add_executable(test_angle test_angle.cpp)

target_link_libraries(test_angle
  PRIVATE
    libwheel::angle
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(test_angle)
