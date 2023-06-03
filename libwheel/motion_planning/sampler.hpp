#ifndef LIBWHEEL_MOTION_PLANNING_SAMPLER_HPP
#define LIBWHEEL_MOTION_PLANNING_SAMPLER_HPP

// Standard library headers
#include <algorithm>
#include <array>
#include <random>

namespace wheel {

template <typename VectorType, typename ScalarType, std::size_t Size>
auto array_to_vector_type(const std::array<ScalarType, Size> &, VectorType &) -> void;

template <typename SpaceType, typename DistributionType, std::size_t max_samples = 100U>
class Sampler {
  public:
    using space_type = SpaceType;
    using vector_type = typename space_type::VectorType;

    explicit Sampler(space_type space) : generator_{random_device_()} {
        static constexpr auto make_distribution = [](const auto &bound_range) {
            return std::uniform_real_distribution<>{bound_range.lower.get(), bound_range.upper.get()};
        };

        std::ranges::transform(std::as_const(space.getBoundRanges()), std::begin(distributions_), make_distribution);
    }

    auto next_sample() -> vector_type {
        std::array<double, vector_type::size> data{};

        std::ranges::transform(distributions_, std::begin(data),
                               [this](auto &distribution) { return distribution(this->generator_); });

        vector_type result{};
        array_to_vector_type(data, result);

        return result;
    }

  private:
    std::random_device random_device_{};
    std::mt19937 generator_;
    std::array<DistributionType, vector_type::size> distributions_;
};

template <typename SpaceType>
using UniformSampler = Sampler<SpaceType, std::uniform_real_distribution<>>;

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_SAMPLER_HPP
