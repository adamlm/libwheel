#ifndef LIBWHEEL_MOTION_PLANNING_SAMPLER_HPP
#define LIBWHEEL_MOTION_PLANNING_SAMPLER_HPP

// Standard library headers
#include <algorithm>
#include <array>
#include <random>

namespace wheel {

template <typename SpaceType, typename DistributionType = std::uniform_real_distribution<>>
class Sampler {
  public:
    using sample_type = typename SpaceType::vector_type;
    using buffer_type = buffer_type_dispatcher_t<sample_type>;

    explicit Sampler(SpaceType space) : generator_{random_device_()} {
        static constexpr auto make_distribution = [](const auto &bound_range) {
            return DistributionType{bound_range.lower, bound_range.upper};
        };

        std::ranges::transform(std::as_const(space.get_bound_ranges()), std::back_inserter(distributions_),
                               make_distribution);
    }

    auto next_sample() -> sample_type {
        buffer_type buffer{};
        ResizeStrategy<buffer_type>::resize(buffer, std::size(distributions_));

        std::ranges::transform(distributions_, std::begin(buffer),
                               [this](auto &distribution) { return distribution(this->generator_); });

        sample_type sample{};
        ResizeStrategy<sample_type>::resize(sample, std::size(distributions_));

        CopyBufferDataStrategy<sample_type, buffer_type>::copy(sample, buffer);

        return sample;
    }

  private:
    std::random_device random_device_{};
    std::mt19937 generator_;
    std::vector<DistributionType> distributions_;
};

template <typename SpaceType>
using UniformSampler = Sampler<SpaceType, std::uniform_real_distribution<>>;

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_SAMPLER_HPP
