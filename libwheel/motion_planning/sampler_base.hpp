#ifndef LIBWHEEL_MOTION_PLANNING_SAMPLER_BASE_HPP
#define LIBWHEEL_MOTION_PLANNING_SAMPLER_BASE_HPP

#include <random>

namespace wheel {

/**
 * @brief Abstract base class for a space sampler
 */
class SamplerBase {
  protected:
    /**
     * @brief Construct a new SamplerBase object
     *
     * This constructor is protected because this class is not meant to be instantiated directly. It is abstract,
     * not concrete.
     */
    explicit SamplerBase() : generator_{random_device_()} {}

    /**
     * @brief Destroy the SamplerBase object
     *
     * This destructor is protected because this class is not concrete, it is abstract. Therefore, we want to prevent
     * polymorphic deletions. See Guideline #4 in Sutter's mill: Virtuality (http://www.gotw.ca/publications/mill18.htm)
     */
    ~SamplerBase() = default;

    std::random_device random_device_{};
    std::mt19937 generator_;
};

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_SAMPLER_BASE_HPP
