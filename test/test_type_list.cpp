#include <string>

#include <libwheel/metaprogramming/type_list.hpp>

// Compile-time tests for TypeList size
static_assert(wheel::TypeList<>::size == 0U);
static_assert(wheel::TypeList<int>::size == 1U);
static_assert(wheel::TypeList<int, int, int>::size == 3U);
static_assert(wheel::TypeList<int, std::string, double>::size == 3U);

// Compile-time tests for index of type within a TypeList
static_assert(wheel::index_of<int, wheel::TypeList<int, char, float>>::value == 0U);
static_assert(wheel::index_of<char, wheel::TypeList<int, char, float>>::value == 1U);
static_assert(wheel::index_of<float, wheel::TypeList<int, char, float>>::value == 2U);
static_assert(wheel::index_of<float, wheel::TypeList<int, float, float>>::value == 1U);

static_assert(!wheel::has_value_member<wheel::index_of<unsigned int, wheel::TypeList<int, char, float>>>);

static_assert(wheel::index_of_v<int, wheel::TypeList<int, char, float>> == 0U);
static_assert(wheel::index_of_v<char, wheel::TypeList<int, char, float>> == 1U);
static_assert(wheel::index_of_v<float, wheel::TypeList<int, char, float>> == 2U);
