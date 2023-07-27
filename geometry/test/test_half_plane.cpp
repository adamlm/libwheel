#include <gtest/gtest.h>
#include <libwheel/geometry/half_plane.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

TEST(HalfPlane, Contains) {
    const wheel::HalfPlane half_plane{wheel::make_line(wheel::Slope{2.0}, wheel::YIntercept{0}),
                                      wheel::Closedness::closed};

    EXPECT_TRUE(wheel::contains(half_plane, wheel::Point2d{0.0, 2.0}));
    EXPECT_FALSE(wheel::contains(half_plane, wheel::Point2d{2.0, 0.0}));
}

TEST(HalfPlane, Complement) {
    const wheel::HalfPlane half_plane{wheel::make_line(wheel::Slope{2.0}, wheel::YIntercept{0}),
                                      wheel::Closedness::closed};

    const auto complemented{wheel::complement(half_plane)};

    EXPECT_TRUE(complemented.closedness != half_plane.closedness);
    EXPECT_FALSE(wheel::linearly_independent(complemented.boundary, half_plane.boundary));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
