#include <array>
#include <iostream>
#include <fstream>

#include <libwheel/motion_planning/uniform_sampler.hpp>
#include <libwheel/motion_planning/space.hpp>
#include <libwheel/motion_planning/bound_range.hpp>

struct CustomVector {
    static constexpr auto kDimensions{3};

    static auto fromArray(const std::array<double, kDimensions>& values) -> CustomVector {
        return CustomVector{
            std::get<0>(values),
            std::get<1>(values),
            std::get<2>(values),
        };
    }

    double foo;
    double bar;
    double baz;
};

using CustomSpace = wheel::Space<CustomVector>;

int main() {
    CustomSpace space{
        wheel::BoundRange{wheel::LowerBound{-5.0}, wheel::UpperBound{5.0}},
        wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}},
        wheel::BoundRange{wheel::LowerBound{20.0}, wheel::UpperBound{30.0}}
    };

    wheel::UniformSampler sampler{space};

    for (auto i{0}; i < 20; ++i) {
        const auto sample{sampler.nextSample()};
        std::cout << sample.foo << ' ' << sample.bar << ' ' << sample.baz << '\n';
    }

    return 0;
}
