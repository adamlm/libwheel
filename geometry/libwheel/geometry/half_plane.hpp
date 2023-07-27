#ifndef LIBWHEEL_GEOMETRY_HALF_PLANE_HPP
#define LIBWHEEL_GEOMETRY_HALF_PLANE_HPP

#include "libwheel/geometry/line.hpp"
#include "libwheel/geometry/point_2d.hpp"

namespace wheel {

enum class Closedness { closed, open };

struct HalfPlane {
    Line boundary;
    Closedness closedness;
};

inline auto contains(const HalfPlane &plane, const Point2d &point) noexcept -> bool {
    if (plane.closedness == Closedness::closed) {
        return plane.boundary.coefficients.dot(Eigen::Vector3<float>{point.x, point.y, 1}) <= 0;
    }

    return plane.boundary.coefficients.dot(Eigen::Vector3<float>{point.x, point.y, 1}) < 0;
}

inline auto complement(const HalfPlane &plane) -> HalfPlane {
    if (plane.closedness == Closedness::closed) {
        return {-plane.boundary, Closedness::open};
    }

    return {-plane.boundary, Closedness::closed};
}

} // namespace wheel

#endif // LIBWHEEL_GEOMETRY_HALF_PLANE_HPP
