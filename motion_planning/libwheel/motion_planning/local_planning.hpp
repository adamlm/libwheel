#ifndef LIBWHEEL_MOTION_PLANNING_LOCAL_PLANNING_HPP
#define LIBWHEEL_MOTION_PLANNING_LOCAL_PLANNING_HPP

#include <boost/geometry.hpp>

#include "libwheel/motion_planning/detail/find_stopping_point.hpp"
#include "libwheel/motion_planning/detail/interpolate_between.hpp"
#include "libwheel/motion_planning/param_types.hpp"

namespace wheel::motion_planning {

struct StraightLinePlanner {
  public:
    explicit StraightLinePlanner(MaxDistance max_distance) : max_distance_{max_distance} {}

    auto operator()(auto const &source, auto const &target) const {
        auto const exceeds_max_distance = [this, &source](auto const &point) {
            return boost::geometry::distance(source, point) >= max_distance_.value;
        };

        auto const stopping_point{detail::find_stopping_point(
            detail::interpolate_between(source, target, detail::MaxStepSize{0.1}), exceeds_max_distance)};

        return std::vector{stopping_point.value()};
    }

  private:
    MaxDistance max_distance_{0.0};
};

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_LOCAL_PLANNING_HPP
