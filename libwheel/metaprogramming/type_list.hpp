#ifndef LIBWHEEL_METAPROGRAMMING_TYPE_LIST_HPP
#define LIBWHEEL_METAPROGRAMMING_TYPE_LIST_HPP

#include <type_traits>

#include "libwheel/metaprogramming/has_value_member.hpp"

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

/**
 * @brief Return the index of a specified type within a TypeList
 *
 * This metafunction returns the index of the type to find in a value member variable. If the type to find is not
 * in the TypeList, the value member variable will not exist.
 *
 * This is the primary template.
 */
template <typename, typename>
struct index_of;

/** @brief Return the index of a specified type within a TypeList
 *
 * This metafunction returns the index of the type to find in a value member variable. If the type to find is not
 * in the TypeList, the value member variable will not exist.
 *
 * This is the partial template specialization for when the type to find is at the front of the TypeList.
 *
 * @tparam FindType Type to search for in the TypeList
 * @tparam RemainingTypes Parameter pack for the remaining types in the TypeList
 */
template <typename FindType, typename... RemainingTypes>
struct index_of<FindType, TypeList<FindType, RemainingTypes...>> : std::integral_constant<std::size_t, 0U> {};

/**
 * @brief Return the index of a specified type within a TypeList
 *
 * This metafunction returns the index of the type to find in a value member variable. If the type to find is not
 * in the TypeList, the value member variable will not exist.
 *
 * This is the partial template specialization for when the type to find is not at the front of the TypeList.
 *
 * @tparam FindType Type to search for in the TypeList
 * @tparam FrontType Type at the front of the TypeList
 * @tparam RemainingTypes Parameter pack for the remaining types in the TypeList
 */
template <typename FindType, typename FrontType, typename... RemainingTypes>
    requires has_value_member<index_of<FindType, TypeList<RemainingTypes...>>>
struct index_of<FindType, TypeList<FrontType, RemainingTypes...>>
    : std::integral_constant<std::size_t, 1U + index_of<FindType, TypeList<RemainingTypes...>>::value> {};

/**
 * @brief Helper template to return the index of a specified type within a TypeList
 *
 * This is an alias for index_of<FindType, TypeList>::value.
 *
 * @tparam FindType Type to search for in the TypeList
 * @tparam TypeList TypeList being searched through
 */
template <typename FindType, typename TypeList>
    requires has_value_member<index_of<FindType, TypeList>>
constexpr auto index_of_v = index_of<FindType, TypeList>::value;

} // namespace wheel

#endif // LIBWHEEL_METAPROGRAMMING_TYPE_LIST_HPP
