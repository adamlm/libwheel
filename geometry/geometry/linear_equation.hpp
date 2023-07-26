#ifndef LIBWHEEL_GEOMETRY_LINEAR_EQUATION_HPP
#define LIBWHEEL_GEOMETRY_LINEAR_EQUATION_HPP

#include <cstdint>

#include <Eigen/Dense>

#include "libwheel/geometry/point_2d.hpp"

namespace wheel {

/**
 * A linear equation
 */
template <std::size_t Dimensions>
struct LinearEquation {
    // From the mathematical representation a_1 * x_1 + a_2 * x_2 + ... + a_n * x_n + b = 0,
    // the expected vector layout is [a_1, a_2, ..., a_n, b].
    Eigen::Vector<float, Dimensions + 1> coefficients;
};

template <std::size_t Dimensions>
auto operator+(LinearEquation<Dimensions> rhs) -> LinearEquation<Dimensions> {
    return rhs;
}

template <std::size_t Dimensions>
auto operator-(LinearEquation<Dimensions> rhs) -> LinearEquation<Dimensions> {
    rhs.coefficients = -rhs.coefficients;
    return rhs;
}

template <std::size_t Dimensions>
auto operator+=(LinearEquation<Dimensions> &lhs, const LinearEquation<Dimensions> &rhs)
    -> LinearEquation<Dimensions> & {
    lhs.coefficients += rhs.coefficients;
    return lhs;
}

template <std::size_t Dimensions>
auto operator+(LinearEquation<Dimensions> lhs, const LinearEquation<Dimensions> &rhs) -> LinearEquation<Dimensions> {
    lhs += rhs;
    return lhs;
}

template <std::size_t Dimensions>
auto operator-=(LinearEquation<Dimensions> &lhs, const LinearEquation<Dimensions> &rhs)
    -> LinearEquation<Dimensions> & {
    lhs.coefficients -= rhs.coefficients;
    return lhs;
}

template <std::size_t Dimensions>
auto operator-(LinearEquation<Dimensions> lhs, const LinearEquation<Dimensions> &rhs) -> LinearEquation<Dimensions> {
    lhs -= rhs;
    return lhs;
}

template <std::size_t Dimensions>
auto operator*=(LinearEquation<Dimensions> &lhs, float rhs) -> LinearEquation<Dimensions> & {
    lhs.coefficients *= rhs;
    return lhs;
}

template <std::size_t Dimensions>
auto operator*(LinearEquation<Dimensions> lhs, float rhs) -> LinearEquation<Dimensions> {
    lhs *= rhs;
    return lhs;
}

template <std::size_t Dimensions>
auto operator*(float lhs, LinearEquation<Dimensions> rhs) -> LinearEquation<Dimensions> {
    rhs *= lhs;
    return rhs;
}

template <std::size_t Dimensions>
auto operator/=(LinearEquation<Dimensions> &lhs, float rhs) -> LinearEquation<Dimensions> & {
    lhs.coefficients /= rhs;
    return lhs;
}

template <std::size_t Dimensions>
auto operator/(LinearEquation<Dimensions> lhs, float rhs) -> LinearEquation<Dimensions> {
    lhs /= rhs;
    return lhs;
}

template <std::size_t Dimensions>
auto operator==(const LinearEquation<Dimensions> &lhs, const LinearEquation<Dimensions> &rhs) -> bool {
    return lhs.coefficients == rhs.coefficients;
}

template <std::size_t Dimensions>
auto almost_equal(const LinearEquation<Dimensions> &lhs, const LinearEquation<Dimensions> &rhs) noexcept -> bool {
    return lhs.coefficients.isApprox(rhs.coefficients);
}

} // namespace wheel

#endif // LIBWHEEL_GEOMETRY_LINEAR_EQUATION_HPP
