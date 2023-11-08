#include <gtest/gtest.h>

#include <libwheel/motion_planning/orthotope.hpp>
#include <libwheel/motion_planning/type_traits.hpp>

struct TestVector {
    double x{0.0};
    double y{0.0};
    double z{0.0};
};

template <>
struct wheel::motion_planning::customization::dimensionality_impl<TestVector>
    : std::integral_constant<std::size_t, 3U> {};

struct TestPolygon {
    std::vector<TestVector> points;
};

template <>
struct wheel::motion_planning::customization::do_axis_aligned_bounding_orthotope<TestPolygon> {
    static auto _(TestPolygon const &polygon) noexcept {

        double min_x{std::numeric_limits<double>::max()};
        double max_x{std::numeric_limits<double>::lowest()};
        double min_y{std::numeric_limits<double>::max()};
        double max_y{std::numeric_limits<double>::lowest()};
        double min_z{std::numeric_limits<double>::max()};
        double max_z{std::numeric_limits<double>::lowest()};

        for (auto const &point : polygon.points) {
            min_x = std::min(min_x, point.x);
            max_x = std::max(max_x, point.x);
            min_y = std::min(min_y, point.y);
            max_y = std::max(max_y, point.y);
            min_z = std::min(min_z, point.z);
            max_z = std::max(max_z, point.z);
        }

        using wheel::motion_planning::DimensionalBound;
        using wheel::motion_planning::Orthotope;

        return Orthotope<dimensionality_v<TestVector>>{DimensionalBound{min_x, max_x}, DimensionalBound{min_y, max_y},
                                                       DimensionalBound{min_z, max_z}};
    }
};

TEST(Orthotope, AxisAlignedBoundingOrthotope) {
    namespace wheel_mp = wheel::motion_planning;

    TestPolygon const polygon{{TestVector{1, 2, 3}, TestVector{-5, -3, 20}, TestVector{0, -1, 5}}};
    auto const orthotope{wheel_mp::axis_aligned_bounding_orthotope(polygon)};

    EXPECT_DOUBLE_EQ(std::get<0>(orthotope.bounds).min, -5);
    EXPECT_DOUBLE_EQ(std::get<0>(orthotope.bounds).max, 1);

    EXPECT_DOUBLE_EQ(std::get<1>(orthotope.bounds).min, -3);
    EXPECT_DOUBLE_EQ(std::get<1>(orthotope.bounds).max, 2);

    EXPECT_DOUBLE_EQ(std::get<2>(orthotope.bounds).min, 3);
    EXPECT_DOUBLE_EQ(std::get<2>(orthotope.bounds).max, 20);
}
