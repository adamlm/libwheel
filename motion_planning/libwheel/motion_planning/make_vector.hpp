#ifndef LIBWHEEL_MOTION_PLANNING_MAKE_VECTOR_HPP
#define LIBWHEEL_MOTION_PLANNING_MAKE_VECTOR_HPP

namespace wheel::motion_planning {

namespace customization {

template <typename T>
struct do_make_vector;

} // namespace customization

template <typename T>
inline constexpr auto make_vector =
    [](auto &&...args) { return customization::do_make_vector<T>::_(std::forward<decltype(args)>(args)...); };

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_MAKE_VECTOR_HPP
