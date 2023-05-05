#ifndef LIBWHEEL_METAPROGRAMMING_TYPE_LIST_HPP
#define LIBWHEEL_METAPROGRAMMING_TYPE_LIST_HPP

#include <type_traits>

namespace wheel {

/**
 * @brief Struct that contains a compile-time list of types
 *
 * @tparam Types Parameter pack containing the TypeList's contained types
 */
template <typename... Types>
struct TypeList {
    /** @brief Number of elements in the TypeList */
    static constexpr auto size{std::integral_constant<std::size_t, sizeof...(Types)>::value};
};

} // namespace wheel

#endif // LIBWHEEL_METAPROGRAMMING_TYPE_LIST_HPP
