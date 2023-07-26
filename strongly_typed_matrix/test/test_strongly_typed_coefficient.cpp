// Third party headers
#include <gtest/gtest.h>
#include <libwheel/strongly_typed_matrix/strongly_typed_coefficient.hpp>

namespace {

struct IdxX {};
struct IdxY {};

} // namespace

TEST(TestStronglyTypedScalar, RawValue) {
    const wheel::StronglyTypedCoefficient<double, IdxX> coeff_1d{1.0};
    EXPECT_DOUBLE_EQ(coeff_1d.raw_value(), 1.0);

    const wheel::StronglyTypedCoefficient<double, IdxX, IdxY> coeff_2d{2.0};
    EXPECT_DOUBLE_EQ(coeff_2d.raw_value(), 2.0);
}

TEST(TestWrapRawValue, TwoDimensional) {
    const auto coeff_2d{wheel::wrap_raw_value<IdxX, IdxY>(2.0)};

    using expected_coeff_type = const wheel::StronglyTypedCoefficient<double, IdxX, IdxY>;
    static_assert(std::is_same_v<decltype(coeff_2d), expected_coeff_type>);

    EXPECT_DOUBLE_EQ(coeff_2d.raw_value(), 2.0);
}

TEST(TestWrapRawValue, OneDimensional) {
    const auto coeff_1d{wheel::wrap_raw_value<IdxX>(1.0)};

    using expected_coeff_type = const wheel::StronglyTypedCoefficient<double, IdxX, wheel::NoIdxType>;
    static_assert(std::is_same_v<decltype(coeff_1d), expected_coeff_type>);

    EXPECT_DOUBLE_EQ(coeff_1d.raw_value(), 1.0);
}
