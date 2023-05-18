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

target_compile_options(unit_tests
  PRIVATE
    -Wall
    -Wextra
    -Wshadow
    -Wnon-virtual-dtor
    -Wpedantic
    -Wold-style-cast
    -Wunused
    -Wconversion
    -Wsign-conversion
    -Wcast-align
    -Woverloaded-virtual
    -Wdouble-promotion
    -Wformat=2
    -Wimplicit-fallthrough
    -Werror
)

gtest_discover_tests(unit_tests)
