#include <iostream>

#include <gtest/gtest.h>

#include <libwheel/motion_planning/space.hpp>

using TestVector = std::vector<float>;
using TestSpace = wheel::Space<TestVector>;

TEST(SpaceTest, TestGetBoundRanges) {
    const wheel::BoundRange x_bounds{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}};
    const wheel::BoundRange y_bounds{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}};
    const wheel::BoundRange z_bounds{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}};

    TestSpace space{x_bounds, y_bounds, z_bounds};

    const auto bounds{space.get_bound_ranges()};

    EXPECT_DOUBLE_EQ(bounds.at(0).lower.get(), x_bounds.lower.get());
    EXPECT_DOUBLE_EQ(bounds.at(1).lower.get(), y_bounds.lower.get());
    EXPECT_DOUBLE_EQ(bounds.at(2).lower.get(), z_bounds.lower.get());
}