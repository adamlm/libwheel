#include <gtest/gtest.h>

#include <libwheel/angle/angle.hpp>

TEST(AngleTest, ConstructorWithinTwoPi) {
    const wheel::Angle<double> angle{5 * std::numbers::pi / 4.0};

    EXPECT_DOUBLE_EQ(angle.getValue(), 5 * std::numbers::pi / 4.0);
}

TEST(AngleTest, ConstructorBeyondTwoPi) {
    const wheel::Angle<double> angle{3 * std::numbers::pi};

    EXPECT_DOUBLE_EQ(angle.getValue(), std::numbers::pi);
}

TEST(AngleTest, ConstructorNegativeWithinTwoPi) {
    const wheel::Angle<double> angle{-5 * std::numbers::pi / 4.0};

    EXPECT_DOUBLE_EQ(angle.getValue(), 3 * std::numbers::pi / 4.0);
}

TEST(AngleTest, ConstructorNegativeBeyondTwoPi) {
    const wheel::Angle<double> angle{-6 * std::numbers::pi};

    // Rounding errors prevent the two values from being within 4 ULP of each other
    EXPECT_NEAR(angle.getValue(), 0.0, 1e-15);
}

TEST(AngleTest, Displacement) {
    using Angle = wheel::Angle<double>;

    const Angle angle_1{std::numbers::pi / 2.0};
    const Angle angle_2{std::numbers::pi};

    EXPECT_DOUBLE_EQ(wheel::displacement(angle_1, angle_2).getValue(), std::numbers::pi / 2.0);
    EXPECT_DOUBLE_EQ(wheel::displacement(angle_2, angle_1).getValue(), -std::numbers::pi / 2.0);
}

TEST(AngleTest, DisplacementOneEighty) {
    using Angle = wheel::Angle<double>;

    const Angle angle_1{0.0};
    const Angle angle_2{std::numbers::pi};

    EXPECT_DOUBLE_EQ(wheel::displacement(angle_1, angle_2).getValue(), std::numbers::pi);
    EXPECT_DOUBLE_EQ(wheel::displacement(angle_2, angle_1).getValue(), -std::numbers::pi);
}

TEST(AngleTest, DisplacementSameAngle) {
    const wheel::Angle<double> angle{3 * std::numbers::pi / 4.0};

    EXPECT_DOUBLE_EQ(wheel::displacement(angle, angle).getValue(), 0.0);
}
