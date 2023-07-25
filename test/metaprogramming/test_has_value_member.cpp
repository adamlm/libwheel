#include <libwheel/metaprogramming/has_value_member.hpp>

/**
 * @brief Test struct that contains a value member variable
 */
struct ValueMember {
    static constexpr auto value{0U};
};

/**
 * @brief Test struct that does not contain a value member variable
 */
struct NoValueMember {};

// Compile-time tests
static_assert(wheel::has_value_member<ValueMember>);
static_assert(!wheel::has_value_member<NoValueMember>);
