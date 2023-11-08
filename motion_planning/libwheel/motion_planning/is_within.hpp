#ifndef LIBWHEEL_MOTION_PLANNING_IS_WITHIN_HPP
#define LIBWHEEL_MOTION_PLANNING_IS_WITHIN_HPP

namespace wheel::motion_planning {

namespace customization {

template <typename Vector, typename Space>
struct do_is_within;

} // namespace customization

inline constexpr auto is_within = [](auto &&vector, auto &&space) {
    return customization::do_is_within<std::remove_cvref_t<decltype(vector)>, std::remove_cvref_t<decltype(space)>>::_(
        std::forward<decltype(vector)>(vector), std::forward<decltype(space)>(space));
};

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_IS_WITHIN_HPP
