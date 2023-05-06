#include <gtest/gtest.h>

#include <libwheel/motion_planning/vector.hpp>

struct X {};
struct Y {};
struct Z {};

using TestVector = wheel::Vector<wheel::IndexTypeList<X, Y, Z>, wheel::StorageTypeList<int, int, int>>;

// Compile-time tests
static_assert(TestVector::size == 3);

TEST(VectorTest, ElementAccess) {
    TestVector vector{1, 2, 3};

    EXPECT_EQ(vector.get<X>(), 1);
    EXPECT_EQ(vector.get<Y>(), 2);
    EXPECT_EQ(vector.get<Z>(), 3);
}

TEST(VectorTest, ElementModification) {
    TestVector vector{1, 2, 3};

    EXPECT_EQ(vector.get<X>(), 1);
    vector.get<X>() = 10;
    EXPECT_EQ(vector.get<X>(), 10);

    EXPECT_EQ(vector.get<Y>(), 2);
    vector.get<Y>() = 20;
    EXPECT_EQ(vector.get<Y>(), 20);

    EXPECT_EQ(vector.get<Z>(), 3);
    vector.get<Z>() = 30;
    EXPECT_EQ(vector.get<Z>(), 30);
}

TEST(VectorTest, MakeRandomVector) {
    struct FixedSeedDevice {
        auto operator()() -> unsigned int { return 42; }
    };

    using DistributionType = std::uniform_int_distribution<>;

    std::array<DistributionType, TestVector::size> distributions{DistributionType{0, 2}, DistributionType{0, 2},
                                                                 DistributionType{0, 2}};

    const auto vector{wheel::make_random_vector<TestVector, DistributionType, FixedSeedDevice>(distributions)};

    EXPECT_EQ(vector.get<X>(), 1);
    EXPECT_EQ(vector.get<Y>(), 2);
    EXPECT_EQ(vector.get<Z>(), 0);
}
