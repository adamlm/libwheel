#ifndef LIBWHEEL_MOTION_PLANNING_TYPE_TRAITS_HPP
#define LIBWHEEL_MOTION_PLANNING_TYPE_TRAITS_HPP

namespace wheel::motion_planning {

namespace customization {

template <typename T>
struct dimensionality_impl {};

} // namespace customization

template <typename T>
struct dimensionality : customization::dimensionality_impl<T> {};

template <typename T>
inline constexpr auto dimensionality_v{dimensionality<T>::value};

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_TYPE_TRAITS_HPP
