add_library(test_metaprogramming
  test_type_list.cpp
  test_has_value_member.cpp
  test_has_type_member.cpp
  test_is_compile_time_invocable_lambda.cpp
)

target_link_libraries(test_metaprogramming
  PRIVATE
    libwheel::metaprogramming
)

target_compile_options(test_metaprogramming
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
