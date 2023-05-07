#include <iostream>

#include <gtest/gtest.h>

#include <libwheel/motion_planning/space.hpp>
#include <libwheel/motion_planning/vector.hpp>

struct X {};
struct Y {};
struct Z {};

using TestVector = wheel::Vector<wheel::IndexTypeList<X, Y, Z>, wheel::StorageTypeList<float, float, float>>;
using TestSpace = wheel::Space<TestVector>;

// Compile-time tests
static_assert(TestSpace::size == 3);

TEST(SpaceTest, TestGetBoundRanges) {
    const wheel::BoundRange x_bounds{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}};
    const wheel::BoundRange y_bounds{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}};
    const wheel::BoundRange z_bounds{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}};

    TestSpace space{x_bounds, y_bounds, z_bounds};

    const auto bounds{space.getBoundRanges()};

    static_assert(std::size(bounds) == 3U);

    EXPECT_DOUBLE_EQ(std::get<0>(bounds).lower.get(), x_bounds.lower.get());
    EXPECT_DOUBLE_EQ(std::get<1>(bounds).lower.get(), y_bounds.lower.get());
    EXPECT_DOUBLE_EQ(std::get<2>(bounds).lower.get(), z_bounds.lower.get());
}
