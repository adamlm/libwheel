#ifndef LIBWHEEL_MOTION_PLANNING_SPACE_HPP
#define LIBWHEEL_MOTION_PLANNING_SPACE_HPP

#include <array>
#include <vector>

#include "libwheel/motion_planning/bound_range.hpp"

namespace wheel {

/**
 * @brief Class representing a mathematical space (set with structure)
 *
 * @tparam SpaceVectorType Mathematical vector type associated with space
 */
template <typename VectorT>
class Space {
  public:
    using VectorType = VectorT;
    using vector_type = VectorType;
    using PathType = std::vector<VectorType>;

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
    auto getBoundRanges() const -> const std::array<wheel::BoundRange, size> & { return bound_ranges_; }

  private:
    std::array<BoundRange, size> bound_ranges_;
};

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_SPACE_HPP
