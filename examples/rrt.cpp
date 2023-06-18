#include <fstream>
#include <iostream>

#include <Eigen/Dense>

#include <libwheel/motion_planning/bound_range.hpp>
// #include <libwheel/motion_planning/r2_space.hpp>
#include <libwheel/motion_planning/rapidly_exploring_random_trees.hpp>
#include <libwheel/motion_planning/sampler.hpp>
#include <libwheel/motion_planning/space.hpp>
#include <libwheel/motion_planning/utils.hpp>

using R2Vector = Eigen::Vector2f;
using R2Space = wheel::Space<R2Vector>;

template <>
struct wheel::CopyBufferDataStrategy<Eigen::Vector2f, std::vector<float>> {
    static auto copy(Eigen::Vector2f &sample, const std::vector<float> &buffer) {
        sample[0] = buffer.at(0);
        sample[1] = buffer.at(1);
    }
};

template <>
struct wheel::ResizeStrategy<Eigen::Vector2f> {
    static auto resize(Eigen::Vector2f & /* sample */, std::size_t /* new_size */) {}
};

namespace wheel {
template <>
auto euclidean_distance(const Eigen::Vector2f &a, const Eigen::Vector2f &b) -> double {
    return (a - b).norm();
}

template <>
auto interpolate(const Eigen::Vector2f &start, const Eigen::Vector2f &stop, std::size_t num_samples)
    -> std::vector<Eigen::Vector2f> {
    std::vector<Eigen::Vector2f> samples;

    const auto step_size = (start - stop) / (num_samples - 1U);
    for (auto i{0U}; i < num_samples; ++i) {
        samples.emplace_back(start + i * step_size);
    }

    return samples;
}
} // namespace wheel

auto main() -> int {
    const R2Space space{wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound(5.0)},
                        wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound(5.0)}};

    wheel::UniformSampler sampler{space};

    const auto path = find_path_rrt(space, R2Vector{2, 3}, R2Vector{1, 1});
    (void)path;

    if (path.has_value()) {
        std::cout << "Path found!\n";
        std::ofstream filename{"path.txt"};

        // std::cout << path.value() << '\n';

        // wheel::printPathNodes(path.value(), filename);
    }

    return 0;
}
