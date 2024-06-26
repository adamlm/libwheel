#ifndef LIBWHEEL_GEOMETRY_LINE_HPP
#define LIBWHEEL_GEOMETRY_LINE_HPP

#include "libwheel/geometry/linear_equation.hpp"
#include "libwheel/geometry/point_2d.hpp"

namespace wheel {

using Line = LinearEquation<2>;

struct Slope {
    float value;
};

struct YIntercept {
    float value;
};

struct XIntercept {
    float value;
};

/**
 * Construct a line specified in slope-intercept form.
 */
inline auto make_line(Slope slope, YIntercept y_intercept) noexcept -> Line {
    return {{slope.value, -1, y_intercept.value}};
}

/**
 * Construct a line specified in point-slope form (or pont-gradient form).
 */
inline auto make_line(Slope slope, const Point2d &point) noexcept -> Line {
    return {{-slope.value, 1, point.x - point.y}};
}

/**
 * Construct a line specified in intercept form.
 */
inline auto make_line(XIntercept x_intercept, YIntercept y_intercept) noexcept -> Line {
    return {{y_intercept.value, x_intercept.value, -x_intercept.value * y_intercept.value}};
}

/**
 * Construct a line specified in two-point form.
 */
inline auto make_line(const Point2d &point_a, const Point2d &point_b) noexcept -> Line {
    return {{point_a.y - point_b.y, point_b.x - point_a.x, point_a.x * point_b.y - point_b.x * point_a.y}};
}

/**
 * Construct a vertical line from x-intercept.
 */
inline auto make_line(XIntercept x_intercept) noexcept -> Line { return {{1, 0, -x_intercept.value}}; }

/**
 * Test if two lines are linearly independent
 */
inline auto linearly_independent(const Line &lhs, const Line &rhs) noexcept -> bool {
    return !(lhs.coefficients.cross(rhs.coefficients)).isZero();
}

} // namespace wheel

#endif // LIBWHEEL_GEOMETRY_LINE_HPP
