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

// Compile-time tests for beginning type for a TypeList
static_assert(std::is_same_v<wheel::begin_type<wheel::TypeList<int>>::type, int>);
static_assert(std::is_same_v<wheel::begin_type<wheel::TypeList<float, int>>::type, float>);
static_assert(std::is_same_v<wheel::begin_type<wheel::TypeList<float, float>>::type, float>);

static_assert(!wheel::has_value_member<wheel::begin_type<wheel::TypeList<>>>);

static_assert(std::is_same_v<wheel::begin_type_t<wheel::TypeList<int>>, int>);
static_assert(std::is_same_v<wheel::begin_type_t<wheel::TypeList<float, int>>, float>);
static_assert(std::is_same_v<wheel::begin_type_t<wheel::TypeList<float, float>>, float>);

// Compile-time tests for next type in a TypeList
static_assert(std::is_same_v<wheel::next_type<int, wheel::TypeList<int, float, char>>::type, float>);
static_assert(std::is_same_v<wheel::next_type<float, wheel::TypeList<int, float, char>>::type, char>);
static_assert(std::is_same_v<wheel::next_type<float, wheel::TypeList<float, float, char>>::type, float>);

static_assert(!wheel::has_type_member<wheel::next_type<char, wheel::TypeList<int, float, char>>>);
static_assert(!wheel::has_type_member<wheel::next_type<char, wheel::TypeList<>>>);

static_assert(std::is_same_v<wheel::next_type_t<int, wheel::TypeList<int, float, char>>, float>);
static_assert(std::is_same_v<wheel::next_type_t<float, wheel::TypeList<int, float, char>>, char>);
static_assert(std::is_same_v<wheel::next_type_t<float, wheel::TypeList<float, float, char>>, float>);
