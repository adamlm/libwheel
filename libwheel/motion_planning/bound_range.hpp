#ifndef LIBWHEEL_MOTION_PLANNING_BOUNDS_HPP
#define LIBWHEEL_MOTION_PLANNING_BOUNDS_HPP

#include <cassert>

#include "libwheel/motion_planning/tagged_value.hpp"

namespace wheel {

/**
 * @brief Wrapped type representing a BoundRange's lower bound
 */
using LowerBound = TaggedValue<float, struct LowerBoundTag>;

/**
 * @brief Wrapped type representing a BoundRange's upper bound
 */
using UpperBound = TaggedValue<float, struct UpperBoundTag>;

/**
 * @brief One-dimensional bounded range between [lower, upper] (inclusive)
 *
 * The lower value must be less than or equal to the upper value
 */
struct BoundRange {

    /**
     * @brief Construct a new BoundRange object
     *
     * @param l Lower range value
     * @param u Upper range value
     */
    explicit BoundRange(LowerBound l, UpperBound u) : lower{l}, upper{u} {
        assert((lower.get() <= upper.get()) && "lower bound must be <= upper bound");
    }

    LowerBound lower;
    UpperBound upper;
};

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_BOUNDS_HPP
