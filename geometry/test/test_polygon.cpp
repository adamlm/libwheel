#include <gtest/gtest.h>
#include <libwheel/geometry/polygon.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST(Polygon, HalfPlanePolygonContains) {
    const wheel::HalfPlanePolygon polygon{
        wheel::HalfPlane{-wheel::make_line(wheel::Slope{2}, wheel::YIntercept{0}), wheel::Closedness::closed},
        wheel::HalfPlane{-wheel::make_line(wheel::XIntercept{0}), wheel::Closedness::closed},
        wheel::HalfPlane{-wheel::make_line(wheel::Slope{-2}, wheel::YIntercept{2}), wheel::Closedness::closed}};

    EXPECT_TRUE(wheel::contains(polygon, wheel::Point2d{0.5, 1.0}));
    EXPECT_FALSE(wheel::contains(polygon, wheel::Point2d{2.0, 1.0}));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
