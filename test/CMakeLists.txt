add_library(test_metaprogramming
  test_type_list.cpp
  test_has_value_member.cpp
)

target_link_libraries(test_metaprogramming
  PRIVATE
    libwheel::metaprogramming
)
