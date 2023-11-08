#ifndef LIBWHEEL_MOTION_PLANNING_TYPE_TRAITS_HPP
#define LIBWHEEL_MOTION_PLANNING_TYPE_TRAITS_HPP

namespace wheel::motion_planning {

namespace customization {

template <typename T>
struct dimensionality_impl {};

template <typename T>
struct vector_type_impl {};

} // namespace customization

template <typename T>
struct dimensionality : customization::dimensionality_impl<T> {};

template <typename T>
inline constexpr auto dimensionality_v{dimensionality<T>::value};

template <typename T>
struct vector_type : customization::vector_type_impl<T> {};

template <typename T>
using vector_type_t = typename vector_type<T>::type;

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_TYPE_TRAITS_HPP
