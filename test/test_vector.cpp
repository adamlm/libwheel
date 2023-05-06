#include <iostream>

#include <gtest/gtest.h>

#include <libwheel/motion_planning/vector.hpp>

struct X {};
struct Y {};
struct Z {};

using TestVector = wheel::Vector<wheel::IndexTypeList<X, Y, Z>, wheel::StorageTypeList<int, int, int>>;
using TestVectorFloat = wheel::Vector<wheel::IndexTypeList<X, Y, Z>, wheel::StorageTypeList<float, float, float>>;

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

TEST(VectorTest, ToStringInt) {
    const TestVector vector{1, 2, 3};

    const auto string{wheel::to_string(vector)};

    EXPECT_STREQ(string.c_str(), "1 2 3");
}

TEST(VectorTest, ToStringFloat) {
    const TestVectorFloat vector{1.2F, 2.4444F, 3.0F};
    const auto string{wheel::to_string(vector)};

    EXPECT_STREQ(string.c_str(), "1.200000 2.444400 3.000000");
}

TEST(VectorTest, EuclideanDistanceOneAxis) {
    const TestVector source{0, 0, 0};
    const TestVector target_x{4, 0, 0};
    const TestVector target_y{0, 5, 0};
    const TestVector target_z{0, 0, 23};

    EXPECT_DOUBLE_EQ(wheel::euclidean_distance(source, target_x), 4.0);
    EXPECT_DOUBLE_EQ(wheel::euclidean_distance(source, target_y), 5.0);
    EXPECT_DOUBLE_EQ(wheel::euclidean_distance(source, target_z), 23.0);
}

TEST(VectorTest, EuclideanDistanceMultiAxis) {
    const TestVectorFloat source{3.455F, -2.5006F, 20.77F};
    const TestVectorFloat target{6.455F, -12.5006F, 0.77F};

    EXPECT_DOUBLE_EQ(wheel::euclidean_distance(source, target), 22.561028662388491);
}

TEST(VectorTest, EuclideanDistanceMultiAxisZero) {
    const TestVectorFloat source{3.455F, -2.5006F, 20.77F};
    const TestVectorFloat target{3.455F, -2.5006F, 20.77F};

    EXPECT_DOUBLE_EQ(wheel::euclidean_distance(source, target), 0.0);
}

TEST(VectorTest, Addition) {
    const TestVector lhs;
    const TestVector rhs;
    const auto result{lhs + rhs};

    EXPECT_EQ(result, TestVector{});
}

TEST(VectorTest, Subtraction) {
    const TestVector lhs;
    const TestVector rhs;
    const auto result{lhs - rhs};

    EXPECT_EQ(result, TestVector{});
}

TEST(VectorTest, Multiplication) {
    const int lhs{2};
    const TestVector rhs;
    const auto result{lhs * rhs};

    EXPECT_EQ(result, TestVector{});
}

TEST(VectorTest, Division) {
    const int lhs{2};
    const TestVector rhs;
    const auto result{rhs / lhs};

    EXPECT_EQ(result, TestVector{});
}

TEST(VectorTest, Interpolate) {
    const TestVectorFloat source{1.0F, 2.0F, 3.0F};
    const TestVectorFloat target{4.0F, 5.0F, 6.0F};

    const std::array<TestVectorFloat, 11U> expected_values{
        TestVectorFloat{1.0F, 2.0F, 3.0F}, TestVectorFloat{1.3F, 2.3F, 3.3F}, TestVectorFloat{1.6F, 2.6F, 3.6F},
        TestVectorFloat{1.9F, 2.9F, 3.9F}, TestVectorFloat{2.2F, 3.2F, 4.2F}, TestVectorFloat{2.5F, 3.5F, 4.5F},
        TestVectorFloat{2.8F, 3.8F, 4.8F}, TestVectorFloat{3.1F, 4.1F, 5.1F}, TestVectorFloat{3.4F, 4.4F, 5.4F},
        TestVectorFloat{3.7F, 4.7F, 5.7F}, TestVectorFloat{4.0F, 5.0F, 6.0F},
    };

    const auto results = wheel::interpolate(source, target, 11U);

    EXPECT_EQ(std::size(results), 11U);

    for (auto i{0U}; i < std::size(results); ++i) {
        EXPECT_FLOAT_EQ(results[i].get<X>(), expected_values[i].get<X>());
        EXPECT_FLOAT_EQ(results[i].get<Y>(), expected_values[i].get<Y>());
        EXPECT_FLOAT_EQ(results[i].get<Z>(), expected_values[i].get<Z>());
    }
}
