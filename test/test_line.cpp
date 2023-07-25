#include <gtest/gtest.h>
#include <libwheel/geometry/line.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

namespace {

class MakeLine : public ::testing::Test {
  protected:
    wheel::Line expected_upward_line_{{4.0F, -1.0F, 1.0F}};
    wheel::Line expected_downward_line_{{-7.0F, -1.0F, 5.0F}};
    wheel::Line expected_horizontal_line_{{0.0F, -1.0F, -3.0F}};
    wheel::Line expected_vertical_line_{{-1.0F, 0.0F, -5.0F}};
};

auto expect_linearly_dependent(const wheel::Line &lhs, const wheel::Line &rhs) noexcept -> void {
    EXPECT_TRUE(!wheel::linearly_independent(lhs, rhs)) << "Lines are linearly independent:\n"
                                                        << "  " << lhs.coefficients.transpose() << "\nvs.\n"
                                                        << "  " << rhs.coefficients.transpose() << '\n';
}

} // namespace

TEST_F(MakeLine, SlopeInterceptForm) {
    // Test doest not apply to vertical line.

    expect_linearly_dependent(wheel::make_line(wheel::Slope{4}, wheel::YIntercept{1}), expected_upward_line_);
    expect_linearly_dependent(wheel::make_line(wheel::Slope{-7}, wheel::YIntercept{5}), expected_downward_line_);
    expect_linearly_dependent(wheel::make_line(wheel::Slope{0}, wheel::YIntercept{-3}), expected_horizontal_line_);
}

TEST_F(MakeLine, PointSlopeForm) {
    // Test doest not apply to vertical line.

    expect_linearly_dependent(wheel::make_line(wheel::Slope{4}, wheel::Point2d{0, 1}), expected_upward_line_);
    expect_linearly_dependent(wheel::make_line(wheel::Slope{-7}, wheel::Point2d{0, 5}), expected_downward_line_);
    expect_linearly_dependent(wheel::make_line(wheel::Slope{0}, wheel::Point2d{0, -3}), expected_horizontal_line_);
}

TEST_F(MakeLine, InterceptForm) {
    // Test doest not apply to horizontal line.
    // Test doest not apply to vertical line.

    expect_linearly_dependent(wheel::make_line(wheel::XIntercept{-1 / 4.0F}, wheel::YIntercept{1}),
                              expected_upward_line_);
    expect_linearly_dependent(wheel::make_line(wheel::XIntercept{5 / 7.0F}, wheel::YIntercept{5}),
                              expected_downward_line_);
}

TEST_F(MakeLine, TwoPointForm) {
    expect_linearly_dependent(wheel::make_line(wheel::Point2d{0, 1}, wheel::Point2d{-1 / 4.0F, 0}),
                              expected_upward_line_);
    expect_linearly_dependent(wheel::make_line(wheel::Point2d{0, 5}, wheel::Point2d{5 / 7.0F, 0}),
                              expected_downward_line_);
    expect_linearly_dependent(wheel::make_line(wheel::Point2d{0, -3}, wheel::Point2d{10, -3}),
                              expected_horizontal_line_);
    expect_linearly_dependent(wheel::make_line(wheel::Point2d{-5, 0}, wheel::Point2d{-5, 10}), expected_vertical_line_);
}

TEST_F(MakeLine, XIntercept) {
    // Test doest not apply to upward line.
    // Test doest not apply to downward line.
    // Test doest not apply to horizontal line.

    expect_linearly_dependent(wheel::make_line(wheel::XIntercept{-5}), expected_vertical_line_);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
