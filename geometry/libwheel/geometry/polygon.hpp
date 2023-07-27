#ifndef LIBWHEEL_GEOMETRY_VERTEX_POLYGON_HPP
#define LIBWHEEL_GEOMETRY_VERTEX_POLYGON_HPP

#include <algorithm>
#include <ranges>

#include <range/v3/view.hpp>

#include "libwheel/geometry/half_plane.hpp"
#include "libwheel/geometry/line.hpp"
#include "libwheel/geometry/point_2d.hpp"

namespace wheel {

/**
 * A polygon defined by intersection a finite number of half-planes.
 *
 * This definition allows the polygon to be unbounded.
 */
struct HalfPlanePolygon {
    explicit HalfPlanePolygon(std::initializer_list<HalfPlane> planes) : boundaries{std::size(planes), 3} {
        for (const auto [index, plane] : ranges::views::enumerate(planes)) {
            if (plane.closedness != Closedness::closed) {
                throw std::invalid_argument("Half-plane must be closed.");
            }

            boundaries.row(static_cast<Eigen::Index>(index)) = plane.boundary.coefficients;
        }
    }

    Eigen::MatrixXf boundaries;
};

inline auto contains(const HalfPlanePolygon &polygon, const Point2d &point) noexcept -> bool {
    return ((polygon.boundaries * Eigen::Vector3f{point.x, point.y, 1}).array() <=
            Eigen::ArrayXf::Zero(polygon.boundaries.rows()))
        .all();
}

} // namespace wheel

#endif // LIBWHEEL_GEOMETRY_VERTEX_POLYGON_HPP
