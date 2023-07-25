#include <libwheel/metaprogramming/has_type_member.hpp>

/**
 * @brief Test struct that contains a type member variable
 */
struct TypeMember {
    using type = int;
};

/**
 * @brief Test struct that does not contain a type member variable
 */
struct NoTypeMember {};

// Compile-time tests
static_assert(wheel::has_type_member<TypeMember>);
static_assert(!wheel::has_type_member<NoTypeMember>);
