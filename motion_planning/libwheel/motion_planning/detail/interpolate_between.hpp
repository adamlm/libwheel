#ifndef LIBWHEEL_MOTION_PLANNING_DETAIL_INTERPOLATE_BETWEEN_HPP
#define LIBWHEEL_MOTION_PLANNING_DETAIL_INTERPOLATE_BETWEEN_HPP

#include <vector>

#include <boost/geometry.hpp>

namespace wheel::motion_planning::detail {

struct MaxStepSize {
    double value{1.0};
};

template <typename Point>
auto interpolate_between(Point const &source, Point const &target, MaxStepSize max_step_size) noexcept
    -> std::vector<Point> {

    auto const num_steps{std::ceil(boost::geometry::distance(source, target) / max_step_size.value)};
    auto const normalized_step_size{1.0 / num_steps};

    std::vector<Point> points;
    for (auto i{0.0}; i < 1.0; i += normalized_step_size) {
        auto scaled_source{source};
        boost::geometry::multiply_value(scaled_source, 1 - i);

        auto scaled_target{target};
        boost::geometry::multiply_value(scaled_target, i);

        boost::geometry::add_point(scaled_source, scaled_target);
        points.push_back(scaled_source);
    }

    return points;
}

} // namespace wheel::motion_planning::detail

#endif // LIBWHEEL_MOTION_PLANNING_DETAIL_INTERPOLATE_BETWEEN_HPP
