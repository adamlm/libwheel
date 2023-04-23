#ifndef LIBWHEEL_MOTION_PLANNING_R2_SPACE_HPP
#define LIBWHEEL_MOTION_PLANNING_R2_SPACE_HPP

#include <array>
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

    double x;
    double y;
};

/**
 * @brief The two-dimensional Euclidean space (R^2)
 */
using R2Space = Space<R2Vector>;

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_R2_SPACE_HPP
