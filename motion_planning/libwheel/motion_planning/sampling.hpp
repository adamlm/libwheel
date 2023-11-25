#ifndef LIBWHEEL_MOTION_PLANNING_SAMPLING_HPP
#define LIBWHEEL_MOTION_PLANNING_SAMPLING_HPP

#include <exception>
#include <initializer_list>

#include <range/v3/view.hpp>

#include "libwheel/motion_planning/attempt_count.hpp"
#include "libwheel/motion_planning/dimensional_bound.hpp"
#include "libwheel/motion_planning/is_within.hpp"
#include "libwheel/motion_planning/make_vector.hpp"
#include "libwheel/motion_planning/type_traits.hpp"

namespace wheel::motion_planning {

struct SamplingError : std::runtime_error {
    using runtime_error::runtime_error;
};

template <typename Space>
class UniformSampler {
  public:
    constexpr explicit UniformSampler(Space const &space) : UniformSampler{space, AttemptCount{100U}} {}

    constexpr explicit UniformSampler(Space const &space, AttemptCount const &max_attempts)
        : space_{std::move(space)}, number_generator_{random_device_()}, max_attempts_{max_attempts} {
        auto const bounding_orthotope{axis_aligned_bounding_orthotope(space)};

        for (auto const &[bound, distribution] : ranges::zip_view(bounding_orthotope.bounds, distributions_)) {
            distribution = std::uniform_real_distribution<>{bound.min, bound.max};
        }
    }

    [[nodiscard]]
    constexpr auto sample_space() -> vector_type_t<Space> {
        for (AttemptCount attempts{0U}; attempts < max_attempts_; ++attempts) {
            std::array<double, dimensionality_v<Space>> random_data{};

            for (auto const &[element, distribution] : ranges::views::zip(random_data, distributions_)) {
                element = distribution(number_generator_);
            }

            if (auto const sample{make_vector<vector_type_t<Space>>(random_data)}; is_within(sample, space_)) {
                return sample;
            }
        }

        throw SamplingError{"exceeded maximum sampling attempts ('" + std::to_string(max_attempts_.attempts) + "')"};
    }

  private:
    Space space_;
    std::random_device random_device_{};
    std::default_random_engine number_generator_;
    std::array<std::uniform_real_distribution<>, dimensionality_v<Space>> distributions_;
    AttemptCount max_attempts_;
};

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_SAMPLING_HPP
