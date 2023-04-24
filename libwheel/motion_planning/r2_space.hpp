#ifndef LIBWHEEL_MOTION_PLANNING_R2_SPACE_HPP
#define LIBWHEEL_MOTION_PLANNING_R2_SPACE_HPP

#include <array>
#include <cmath>
#include <sstream>
#include <string>

#include "libwheel/motion_planning/space.hpp"

namespace wheel {

/**
 * @brief A mathematical vector in the two-dimensional Euclidean space (R^2)
 */
struct R2Vector {
    static constexpr auto kDimensions{2};

    /**
     * @brief Create an R2Vector from a std::array
     *
     * @param values Vector values in order x, y
     * @return R2Vector R2Vector instance copied from the std::array
     */
    static auto fromArray(const std::array<double, kDimensions>& values) -> R2Vector {
        return R2Vector{
            std::get<0>(values),
            std::get<1>(values),
        };
    }

    /**
     * @brief Create a std::string representation of the R2Vector
     *
     * @param vector R2Vector being converted to a std::string
     * @param delimiter Character separating vector elements
     * @return std::string String representation of specified R2Vector
     */
    static auto toString(const R2Vector& vector, char delimiter = ' ') -> std::string {
        std::stringstream stream;

        stream << vector.x << delimiter << vector.y;

        return stream.str();
    }

    /**
     * @brief Calculate the distance between two R2Vectors
     *
     * This function implements the Euclidean distance
     *
     * @param a First R2Vector
     * @param b Second R2Vector
     * @return double Euclidean distance between R2Vectors
     */
    static auto distance(const R2Vector& a, const R2Vector& b) -> double {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }

    static auto interpolate(const R2Vector &source, const R2Vector &target, std::size_t num_samples) -> std::vector<wheel::R2Vector> {
    std::vector<wheel::R2Vector> configs;

    const auto step_x{(target.x - source.x) / num_samples};
    const auto step_y{(target.y - source.y) / num_samples};

    for (auto i{1}; i <= num_samples; ++i) {
        configs.emplace_back(wheel::R2Vector{source.x + i * step_x, source.y + i * step_y});
    }

    return configs;
}

    double x;
    double y;
};

/**
 * @brief The two-dimensional Euclidean space (R^2)
 */
using R2Space = Space<R2Vector>;

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_R2_SPACE_HPP
