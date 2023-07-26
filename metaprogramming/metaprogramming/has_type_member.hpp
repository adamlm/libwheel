#ifndef LIBWHEEL_METAPROGRAMMING_HAS_TYPE_MEMBER_HPP
#define LIBWHEEL_METAPROGRAMMING_HAS_TYPE_MEMBER_HPP

namespace wheel {

/**
 * @brief Check if specified type has a type member variable
 *
 * Concept is satisfied only if specified type has a type member variable.
 *
 * @tparam T Type being checked
 */
template <typename T>
concept has_type_member = requires { typename T::type; };

} // namespace wheel

#endif // LIBWHEEL_METAPROGRAMMING_HAS_TYPE_MEMBER_HPP
