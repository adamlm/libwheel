#ifndef LIBWHEEL_MOTION_PLANNING_LOCAL_PLANNING_HPP
#define LIBWHEEL_MOTION_PLANNING_LOCAL_PLANNING_HPP

#include <boost/geometry.hpp>

#include "libwheel/motion_planning/detail/find_stopping_point.hpp"
#include "libwheel/motion_planning/detail/interpolate_between.hpp"
#include "libwheel/motion_planning/param_types.hpp"

namespace wheel::motion_planning {

template <typename Space>
struct StraightLinePlanner {
  public:
    explicit StraightLinePlanner(Space space, MaxDistance max_distance)
        : space_{std::move(space)}, max_distance_{max_distance} {}

    auto operator()(auto const &source, auto const &target) const {
        auto const should_stop = [this, &source](auto const &point) {
            return boost::geometry::distance(source, point) >= max_distance_.value || !is_within(point, this->space_);
        };

        auto const stopping_point{detail::find_stopping_point(
            detail::interpolate_between(source, target, detail::MaxStepSize{0.1}), should_stop)};

        return std::vector{stopping_point.value()};
    }

  private:
    Space space_;
    MaxDistance max_distance_{0.0};
};

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_LOCAL_PLANNING_HPP
