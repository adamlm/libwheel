#include <gtest/gtest.h>

#include <libwheel/metaprogramming/type_list.hpp>
#include <libwheel/strongly_typed_matrix/strongly_typed_matrix.hpp>

struct IdxX {};
struct IdxY {};
struct IdxZ {};

using RowIdxList = wheel::TypeList<IdxX, IdxY, IdxZ>;
using ColIdxList = wheel::TypeList<IdxX, IdxY, IdxZ>;

using TestMatrix = wheel::StronglyTypedMatrix<double, RowIdxList, ColIdxList, struct TestMatrixTag>;
using TestVector = wheel::StronglyTypedVector<double, RowIdxList, struct TestVectorTag>;

TEST(TestStronglyTypedMatrix, MutableElementAccess) {
    TestMatrix matrix{wheel::wrap_raw_value<IdxX, IdxX>(1.0), wheel::wrap_raw_value<IdxX, IdxY>(2.0),
                      wheel::wrap_raw_value<IdxX, IdxZ>(3.0), wheel::wrap_raw_value<IdxY, IdxX>(4.0),
                      wheel::wrap_raw_value<IdxY, IdxY>(5.0), wheel::wrap_raw_value<IdxY, IdxZ>(6.0),
                      wheel::wrap_raw_value<IdxZ, IdxX>(7.0), wheel::wrap_raw_value<IdxZ, IdxY>(8.0),
                      wheel::wrap_raw_value<IdxZ, IdxZ>(9.0)};

    EXPECT_DOUBLE_EQ((matrix.at<IdxX, IdxX>()), 1.0);
    matrix.at<IdxX, IdxX>() = 10.0;
    EXPECT_DOUBLE_EQ((matrix.at<IdxX, IdxX>()), 10.0);

    EXPECT_DOUBLE_EQ((matrix.at<IdxZ, IdxZ>()), 9.0);
    matrix.at<IdxZ, IdxZ>() = 90.0;
    EXPECT_DOUBLE_EQ((matrix.at<IdxZ, IdxZ>()), 90.0);
}

TEST(TestStronglyTypedMatrix, ConstElementAccess) {
    const TestMatrix matrix{wheel::wrap_raw_value<IdxX, IdxX>(1.0), wheel::wrap_raw_value<IdxX, IdxY>(2.0),
                            wheel::wrap_raw_value<IdxX, IdxZ>(3.0), wheel::wrap_raw_value<IdxY, IdxX>(4.0),
                            wheel::wrap_raw_value<IdxY, IdxY>(5.0), wheel::wrap_raw_value<IdxY, IdxZ>(6.0),
                            wheel::wrap_raw_value<IdxZ, IdxX>(7.0), wheel::wrap_raw_value<IdxZ, IdxY>(8.0),
                            wheel::wrap_raw_value<IdxZ, IdxZ>(9.0)};

    EXPECT_DOUBLE_EQ((matrix.at<IdxX, IdxX>()), 1.0);
    EXPECT_DOUBLE_EQ((matrix.at<IdxZ, IdxZ>()), 9.0);
}

TEST(TestStronglyTypedMatrix, MutableRawMatrixAccess) {
    TestMatrix matrix{wheel::wrap_raw_value<IdxX, IdxX>(1.0), wheel::wrap_raw_value<IdxX, IdxY>(2.0),
                      wheel::wrap_raw_value<IdxX, IdxZ>(3.0), wheel::wrap_raw_value<IdxY, IdxX>(4.0),
                      wheel::wrap_raw_value<IdxY, IdxY>(5.0), wheel::wrap_raw_value<IdxY, IdxZ>(6.0),
                      wheel::wrap_raw_value<IdxZ, IdxX>(7.0), wheel::wrap_raw_value<IdxZ, IdxY>(8.0),
                      wheel::wrap_raw_value<IdxZ, IdxZ>(9.0)};
    auto &raw_matrix{matrix.raw_matrix()};

    EXPECT_DOUBLE_EQ(raw_matrix(0, 0), 1.0);
    raw_matrix(0, 0) = 10.0;
    EXPECT_DOUBLE_EQ(raw_matrix(0, 0), 10.0);
    EXPECT_DOUBLE_EQ((matrix.at<IdxX, IdxX>()), 10.0);

    EXPECT_DOUBLE_EQ(raw_matrix(2, 2), 9.0);
    raw_matrix(2, 2) = 90.0;
    EXPECT_DOUBLE_EQ(raw_matrix(2, 2), 90.0);
    EXPECT_DOUBLE_EQ((matrix.at<IdxZ, IdxZ>()), 90.0);
}

TEST(TestStronglyTypedMatrix, ConstRawMatrixAccess) {
    const TestMatrix matrix{wheel::wrap_raw_value<IdxX, IdxX>(1.0), wheel::wrap_raw_value<IdxX, IdxY>(2.0),
                            wheel::wrap_raw_value<IdxX, IdxZ>(3.0), wheel::wrap_raw_value<IdxY, IdxX>(4.0),
                            wheel::wrap_raw_value<IdxY, IdxY>(5.0), wheel::wrap_raw_value<IdxY, IdxZ>(6.0),
                            wheel::wrap_raw_value<IdxZ, IdxX>(7.0), wheel::wrap_raw_value<IdxZ, IdxY>(8.0),
                            wheel::wrap_raw_value<IdxZ, IdxZ>(9.0)};
    const auto &raw_matrix{matrix.raw_matrix()};

    EXPECT_DOUBLE_EQ(raw_matrix(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(raw_matrix(2, 2), 9.0);
}

TEST(TestStronglyTypedVector, MutableElementAccess) {
    TestVector vector{wheel::wrap_raw_value<IdxX>(1.0), wheel::wrap_raw_value<IdxY>(2.0),
                      wheel::wrap_raw_value<IdxZ>(3.0)};

    EXPECT_DOUBLE_EQ((vector.at<IdxX>()), 1.0);
    vector.at<IdxX>() = 10.0;
    EXPECT_DOUBLE_EQ((vector.at<IdxX>()), 10.0);

    EXPECT_DOUBLE_EQ((vector.at<IdxZ>()), 3.0);
    vector.at<IdxZ>() = 30.0;
    EXPECT_DOUBLE_EQ((vector.at<IdxZ>()), 30.0);
}

TEST(TestStronglyTypedVector, ConstElementAccess) {
    const TestVector vector{wheel::wrap_raw_value<IdxX>(1.0), wheel::wrap_raw_value<IdxY>(2.0),
                            wheel::wrap_raw_value<IdxZ>(3.0)};

    EXPECT_DOUBLE_EQ((vector.at<IdxX>()), 1.0);
    EXPECT_DOUBLE_EQ((vector.at<IdxZ>()), 3.0);
}

TEST(TestStronglyTypedVector, MutableRawMatrixAccess) {
    TestVector vector{wheel::wrap_raw_value<IdxX>(1.0), wheel::wrap_raw_value<IdxY>(2.0),
                      wheel::wrap_raw_value<IdxZ>(3.0)};
    auto &raw_vector{vector.raw_matrix()};

    EXPECT_DOUBLE_EQ(raw_vector(0), 1.0);
    raw_vector(0) = 10.0;
    EXPECT_DOUBLE_EQ(raw_vector(0), 10.0);
    EXPECT_DOUBLE_EQ((vector.at<IdxX>()), 10.0);

    EXPECT_DOUBLE_EQ(raw_vector(2), 3.0);
    raw_vector(2) = 30.0;
    EXPECT_DOUBLE_EQ(raw_vector(2), 30.0);
    EXPECT_DOUBLE_EQ((vector.at<IdxZ>()), 30.0);
}

TEST(TestStronglyTypedVector, ConstRawMatrixAccess) {
    const TestVector vector{wheel::wrap_raw_value<IdxX>(1.0), wheel::wrap_raw_value<IdxY>(2.0),
                            wheel::wrap_raw_value<IdxZ>(3.0)};
    const auto &raw_vector{vector.raw_matrix()};

    EXPECT_DOUBLE_EQ(raw_vector(0), 1.0);
    EXPECT_DOUBLE_EQ(raw_vector(2), 3.0);
}
