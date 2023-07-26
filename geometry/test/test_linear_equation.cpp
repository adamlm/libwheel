#include <gtest/gtest.h>
#include <libwheel/geometry/linear_equation.hpp>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

using TestLinearEquation = wheel::LinearEquation<4>;

TEST(LinearEquation, Identity) {
    const TestLinearEquation equation{{1, 2, 3, 4, 5}};

    EXPECT_TRUE(wheel::almost_equal(+equation, equation));
}

TEST(LinearEquation, Negation) {
    const TestLinearEquation equation{{1, 2, 3, 4, 5}};
    const TestLinearEquation expected_results{{-1, -2, -3, -4, -5}};

    EXPECT_TRUE(wheel::almost_equal(-equation, expected_results));
}

TEST(LinearEquation, ScalarMultiplicationAssign) {
    TestLinearEquation equation{{1, 2, 3, 4, 5}};
    const TestLinearEquation expected_results{{2, 4, 6, 8, 10}};

    equation *= 2;
    EXPECT_TRUE(wheel::almost_equal(equation, expected_results));
}

TEST(LinearEquation, ScalarMultiplication) {
    const TestLinearEquation equation{{1, 2, 3, 4, 5}};
    const TestLinearEquation expected_results{{2, 4, 6, 8, 10}};

    EXPECT_TRUE(wheel::almost_equal(2 * equation, expected_results));
    EXPECT_TRUE(wheel::almost_equal(equation * 2, expected_results));
}

TEST(LinearEquation, ScalarDivisionAssignment) {
    TestLinearEquation equation{{1, 2, 3, 4, 5}};
    const TestLinearEquation expected_results{{0.5, 1, 1.5, 2, 2.5}};

    equation /= 2;
    EXPECT_TRUE(wheel::almost_equal(equation, expected_results));
}

TEST(LinearEquation, ScalarDivision) {
    const TestLinearEquation equation{{1, 2, 3, 4, 5}};
    const TestLinearEquation expected_results{{0.5, 1, 1.5, 2, 2.5}};

    EXPECT_TRUE(wheel::almost_equal(equation / 2, expected_results));
}

TEST(LinearEquation, EquationAdditionAssignment) {
    TestLinearEquation equation_a{{1, 2, 3, 4, 5}};
    const TestLinearEquation equation_b{{6, 7, 8, 9, 10}};
    const TestLinearEquation expected_results{{7, 9, 11, 13, 15}};

    equation_a += equation_b;
    EXPECT_TRUE(wheel::almost_equal(equation_a, expected_results));
}

TEST(LinearEquation, EquationAddition) {
    const TestLinearEquation equation_a{{1, 2, 3, 4, 5}};
    const TestLinearEquation equation_b{{6, 7, 8, 9, 10}};
    const TestLinearEquation expected_results{{7, 9, 11, 13, 15}};

    EXPECT_TRUE(wheel::almost_equal(equation_a + equation_b, expected_results));
    EXPECT_TRUE(wheel::almost_equal(equation_b + equation_a, expected_results));
}

TEST(LinearEquation, EquationSubtractionAssignment) {
    TestLinearEquation equation_a{{1, 2, 3, 4, 5}};
    const TestLinearEquation equation_b{{6, 7, 8, 9, 10}};
    const TestLinearEquation expected_results{{-5, -5, -5, -5, -5}};

    equation_a -= equation_b;
    EXPECT_TRUE(wheel::almost_equal(equation_a, expected_results));
}

TEST(LinearEquation, EquationSubtraction) {
    const TestLinearEquation equation_a{{1, 2, 3, 4, 5}};
    const TestLinearEquation equation_b{{6, 7, 8, 9, 10}};
    const TestLinearEquation expected_results{{-5, -5, -5, -5, -5}};

    EXPECT_TRUE(wheel::almost_equal(equation_a - equation_b, expected_results));
}

TEST(LinearEquation, ExactEquality) {
    const TestLinearEquation equation_a{{1.0, 2.0, 3.5, 4.5, 1.25}};
    const TestLinearEquation equation_b{{1.0, 2.0, 3.5, 4.5, 1.25}};
    const TestLinearEquation equation_c{{6, 7, 8, 9, 10}};

    EXPECT_EQ(equation_a, equation_b);
    EXPECT_NE(equation_a, equation_c);
}

TEST(LinearEquation, AlmostEquality) {
    const TestLinearEquation equation_a{{1.0, 2.0, 3.5, 4.5, 1.25}};
    const TestLinearEquation equation_b{{1.0F, 2.0000000001F, 3.5000000001F, 4.4999999999F, 1.25F}};
    const TestLinearEquation equation_c{{1.0F, 2.001F, 3.5F, 4.4F, 1.26F}};

    EXPECT_TRUE(wheel::almost_equal(equation_a, equation_b));
    EXPECT_FALSE(wheel::almost_equal(equation_a, equation_c));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
