#ifndef LIBWHEEL_MOTION_PLANNING_EXTERNAL_BOOST_GEOMETRY_HPP
#define LIBWHEEL_MOTION_PLANNING_EXTERNAL_BOOST_GEOMETRY_HPP

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include "libwheel/motion_planning/is_within.hpp"
#include "libwheel/motion_planning/make_vector.hpp"
#include "libwheel/motion_planning/orthotope.hpp"
#include "libwheel/motion_planning/type_traits.hpp"

template <typename Point>
struct wheel::motion_planning::customization::vector_type_impl<boost::geometry::model::polygon<Point>> {
    using type = typename boost::geometry::model::polygon<Point>::point_type;
};

template <typename Point>
struct wheel::motion_planning::customization::dimensionality_impl<boost::geometry::model::polygon<Point>>
    : std::integral_constant<std::size_t, boost::geometry::dimension<boost::geometry::model::polygon<Point>>::value> {};

template <typename Point>
struct wheel::motion_planning::customization::do_is_within<Point, boost::geometry::model::polygon<Point>> {
    static auto _(Point const &point, boost::geometry::model::polygon<Point> const &space) noexcept -> bool {
        return boost::geometry::within(point, space);
    }
};

template <typename Point>
struct wheel::motion_planning::customization::do_is_within<boost::geometry::model::polygon<Point>,
                                                           boost::geometry::model::polygon<Point>> {
    static auto _(boost::geometry::model::polygon<Point> const &subspace,
                  boost::geometry::model::polygon<Point> const &space) noexcept -> bool {
        return boost::geometry::within(subspace, space);
    }
};

template <>
struct wheel::motion_planning::customization::do_make_vector<
    boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>> {
    static auto _(std::array<double, 2U> const &data) noexcept {
        return boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>{std::get<0>(data),
                                                                                        std::get<1>(data)};
    }
};

template <>
struct wheel::motion_planning::customization::do_axis_aligned_bounding_orthotope<
    boost::geometry::model::polygon<boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>>> {
    static auto
    _(boost::geometry::model::polygon<boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>> const
          &space) noexcept {
        double min_x{std::numeric_limits<double>::max()};
        double max_x{std::numeric_limits<double>::lowest()};
        double min_y{std::numeric_limits<double>::max()};
        double max_y{std::numeric_limits<double>::lowest()};

        for (auto const &point : space.outer()) {
            min_x = std::min(min_x, point.get<0>());
            max_x = std::max(max_x, point.get<0>());
            min_y = std::min(min_y, point.get<1>());
            max_y = std::max(max_y, point.get<1>());
        }

        using wheel::motion_planning::DimensionalBound;
        using wheel::motion_planning::Orthotope;

        return Orthotope<dimensionality_v<
            boost::geometry::model::polygon<boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>>>>{
            DimensionalBound{min_x, max_x}, DimensionalBound{min_y, max_y}};
    };
};

#endif // LIBWHEEL_MOTION_PLANNING_EXTERNAL_BOOST_GEOMETRY_HPP
