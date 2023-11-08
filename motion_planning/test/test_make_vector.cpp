#include <gtest/gtest.h>

#include <libwheel/motion_planning/make_vector.hpp>

struct TestVector {
    double x{0.0};
    double y{0.0};
    double z{0.0};
};

template <>
struct wheel::motion_planning::customization::do_make_vector<TestVector> {
    static auto _(std::array<double, 3> const &data) noexcept -> TestVector {
        return {.x = std::get<0>(data), .y = std::get<1>(data), .z = std::get<2>(data)};
    }
};

TEST(MakeVector, Simple) {
    namespace wheel_mp = wheel::motion_planning;

    auto const test_vector{wheel_mp::make_vector<TestVector>(std::array<double, 3>{1, 20, 45})};

    EXPECT_DOUBLE_EQ(test_vector.x, 1);
    EXPECT_DOUBLE_EQ(test_vector.y, 20);
    EXPECT_DOUBLE_EQ(test_vector.z, 45);
}
