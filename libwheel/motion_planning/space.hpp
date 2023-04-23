#ifndef LIBWHEEL_MOTION_PLANNING_SPACE_HPP
#define LIBWHEEL_MOTION_PLANNING_SPACE_HPP

#include <array>

#include "libwheel/motion_planning/bound_range.hpp"

namespace wheel
{

/**
 * @brief Class representing a mathematical space (set with structure)
 *
 * @tparam SpaceVectorType Mathematical vector type associated with space
 */
template <typename SpaceVectorType>
class Space {
public:
    using VectorType = SpaceVectorType;
    static constexpr auto kDimensions{VectorType::kDimensions};

    /**
     * @brief Construct a new Space object
     *
     * @tparam BoundRangeType Sequence of BoundedRange types, one for each dimension
     * @param bound_ranges Bounded range for each space dimension
     */
    template <typename... BoundRangeType>
    explicit Space(BoundRangeType... bound_ranges) : bound_ranges_{bound_ranges...} {}

    /**
     * @brief Get the Space's bound ranges
     *
     * @return const std::array<wheel::BoundRange, kDimensions>& Immutable reference to the space's bound ranges
     */
    auto getBoundRanges() const -> const std::array<wheel::BoundRange, kDimensions>& {
        return bound_ranges_;
    }

private:
    std::array<BoundRange, kDimensions> bound_ranges_;
};

} // namespace wheel


#endif // LIBWHEEL_MOTION_PLANNING_SPACE_HPP
