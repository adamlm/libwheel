#ifndef LIBWHEEL_MOTION_PLANNING_SPACE_HPP
#define LIBWHEEL_MOTION_PLANNING_SPACE_HPP

#include <array>
#include <cassert>
#include <vector>

namespace wheel {

/**
 * @brief Wrapped type representing a BoundRange's lower bound
 */
struct LowerBound {
    double value;
};

/**
 * @brief Wrapped type representing a BoundRange's upper bound
 */
struct UpperBound {
    double value;
};

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
        assert((lower.value <= upper.value) && "lower bound must be <= upper bound");
    }

    LowerBound lower;
    UpperBound upper;
};

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
    auto get_bound_ranges() const -> const std::vector<wheel::BoundRange> & { return bound_ranges_; }

  private:
    std::vector<BoundRange> bound_ranges_;
};

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_SPACE_HPP
