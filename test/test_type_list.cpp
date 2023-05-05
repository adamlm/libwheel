#include <string>

#include <libwheel/metaprogramming/type_list.hpp>

static_assert(wheel::TypeList<>::size == 0U);
static_assert(wheel::TypeList<int>::size == 1U);
static_assert(wheel::TypeList<int, int, int>::size == 3U);
static_assert(wheel::TypeList<int, std::string, double>::size == 3U);
