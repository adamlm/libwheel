#ifndef LIBWHEEL_MOTION_PLANNING_FIND_PATH_HPP
#define LIBWHEEL_MOTION_PLANNING_FIND_PATH_HPP

#include "libwheel/motion_planning/type_traits.hpp"

namespace wheel::motion_planning {

namespace customization {

template <typename>
struct do_find_path;

} // namespace customization

inline constexpr auto find_path = [](auto space, auto start, auto goal, auto strategy, auto visitor) {
    return customization::do_find_path<search_algorithm_category_t<std::remove_cvref_t<decltype(strategy)>>>::_(
        space, start, goal, strategy, visitor);
};

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_FIND_PATH_HPP
