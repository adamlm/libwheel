#ifndef LIBWHEEL_MOTION_PLANNING_UNIFORM_SAMPLER_HPP
#define LIBWHEEL_MOTION_PLANNING_UNIFORM_SAMPLER_HPP

#include <array>
#include <algorithm>

#include "libwheel/motion_planning/sampler_base.hpp"

namespace wheel {

/**
 * @brief A sampler that uniformly samples a given space
 *
 * @tparam SpaceType Space to be sampled
 */
template <typename SpaceT>
class UniformSampler : public SamplerBase {
  public:
    using SpaceType = SpaceT;
    using VectorType = typename SpaceType::VectorType;

    /**
     * @brief Construct a new UniformSampler object
     *
     * @param space Space to be sampled
     */
    explicit UniformSampler(const SpaceType& space) {
        static constexpr auto make_distribution = [](const auto &range) {
            return std::uniform_real_distribution<>{range.lower.get(), range.upper.get()};
        };

        std::ranges::transform(std::as_const(space.getBoundRanges()), std::begin(distributions_), make_distribution);
    }

    /**
     * @brief Get the next sample from the space
     *
     * @return VectorType Mathematical vector contained within the space
     */
    auto nextSample() -> VectorType {
        std::array<double, SpaceType::kDimensions> sampled_values;

        for (auto i{0}; i < std::size(sampled_values); ++i) {
            sampled_values.at(i) = distributions_.at(i)(generator_);
        }

        return VectorType::fromArray(sampled_values);
    }

  private:
    std::array<std::uniform_real_distribution<>, SpaceType::kDimensions> distributions_;
};

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_UNIFORM_SAMPLER_HPP
