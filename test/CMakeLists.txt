add_executable(strongly_typed_matrix_tests
  test_strongly_typed_matrix.cpp
)

target_link_libraries(strongly_typed_matrix_tests
  PRIVATE
    libwheel::strongly_typed_matrix
    GTest::GTest
    GTest::Main
)

target_compile_options(strongly_typed_matrix_tests
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

include(GoogleTest)
gtest_discover_tests(strongly_typed_matrix_tests)
