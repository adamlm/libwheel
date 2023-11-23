#include <boost/geometry.hpp>
#include <fmt/core.h>
#include <libwheel/motion_planning/orthotope.hpp>
#include <libwheel/motion_planning/rapidly_exploring_random_trees.hpp>

using point_t = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>;
using polygon_t = boost::geometry::model::polygon<point_t>;

template <>
struct wheel::motion_planning::customization::vector_type_impl<polygon_t> {
    using type = point_t;
};

template <>
struct wheel::motion_planning::customization::dimensionality_impl<polygon_t>
    : std::integral_constant<std::size_t, boost::geometry::dimension<polygon_t>::value> {};

template <>
struct wheel::motion_planning::customization::do_is_within<point_t, polygon_t> {
    static auto _(point_t const &point, polygon_t const &space) noexcept -> bool {
        return boost::geometry::within(point, space);
    }
};

template <>
struct wheel::motion_planning::customization::do_is_within<polygon_t, polygon_t> {
    static auto _(polygon_t const &subspace, polygon_t const &space) noexcept -> bool {
        return boost::geometry::within(subspace, space);
    }
};

template <>
struct wheel::motion_planning::customization::do_make_vector<point_t> {
    static auto _(std::array<double, 2U> const &data) noexcept { return point_t{std::get<0>(data), std::get<1>(data)}; }
};

template <>
struct wheel::motion_planning::customization::do_axis_aligned_bounding_orthotope<polygon_t> {
    static auto _(polygon_t const &space) noexcept {
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

        return Orthotope<dimensionality_v<polygon_t>>{DimensionalBound{min_x, max_x}, DimensionalBound{min_y, max_y}};
    };
};

auto main() -> int {
    fmt::print("Searching for path\n");

    namespace wheel_mp = wheel::motion_planning;

    // polygon_t polygon{{{0.0, 0.0}, {0.0, 5.0}, {5.0, 5.0}, {5.0, 0.0}, {0.0, 0.0}},
    //                   {{1.0, 1.0}, {4.0, 1.0}, {4.0, 4.0}, {1.0, 4.0}, {1.0, 1.0}}};
    polygon_t polygon{{{0.0, 0.0}, {0.0, 5.0}, {5.0, 5.0}, {5.0, 0.0}, {0.0, 0.0}}};

    wheel::motion_planning::RapidlyExploringRandomTrees rrt{wheel_mp::IterationCount{1U}};

    polygon_t goal_region{{{1.0, 1.0}, {1.0, 2.0}, {2.0, 2.0}, {2.0, 1.0}, {1.0, 1.0}}};

    struct PrintPointVisitor {
        auto on_sample(point_t const &point) const noexcept -> void {
            fmt::print("{} {}\n", point.get<0>(), point.get<1>());
        }
    };

    if (auto const result{rrt(polygon, point_t(0.1, 0.1), goal_region, PrintPointVisitor{})}; result) {
        fmt::print("Path found\n");
        return 0;
    }

    fmt::print("Path not found\n");
    return 1;
}
