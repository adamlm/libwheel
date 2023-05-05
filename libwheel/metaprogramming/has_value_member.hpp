#ifndef LIBWHEEL_METAPROGRAMMING_HAS_VALUE_MEMBER_HPP
#define LIBWHEEL_METAPROGRAMMING_HAS_VALUE_MEMBER_HPP

namespace wheel {

/**
 * @brief Check if specified type has a value member variable
 *
 * Concept is satisfied only if specified type has a value member variable.
 *
 * @tparam T Type being checked
 */
template <typename T>
concept has_value_member = requires { T::value; };

} // namespace wheel

#endif // LIBWHEEL_METAPROGRAMMING_HAS_VALUE_MEMBER_HPP
