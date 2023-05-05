add_library(test_metaprogramming
  test_type_list.cpp
)

target_link_libraries(test_metaprogramming
  PRIVATE
    libwheel::metaprogramming
)
