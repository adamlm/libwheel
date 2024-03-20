#ifndef LIBWHEEL_MOTION_PLANNING_LOCAL_PLANNING_HPP
#define LIBWHEEL_MOTION_PLANNING_LOCAL_PLANNING_HPP

#include <boost/geometry.hpp>

#include "libwheel/motion_planning/detail/find_stopping_point.hpp"
#include "libwheel/motion_planning/detail/interpolate_between.hpp"

namespace wheel::motion_planning {

namespace detail {

struct straight_line_planner {

    auto operator()(auto const &source, auto const &target) const {
        auto const exceeds_max_distance = [&source](auto const &point) {
            return boost::geometry::distance(source, point) >= 1.0;
        };

        auto const stopping_point{detail::find_stopping_point(
            detail::interpolate_between(source, target, detail::MaxStepSize{0.1}), exceeds_max_distance)};

        return std::vector{stopping_point.value()};
    }
};

} // namespace detail

inline constexpr detail::straight_line_planner straight_line_planner{};

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_LOCAL_PLANNING_HPP
