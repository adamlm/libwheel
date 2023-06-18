#include <fstream>
#include <iostream>

#include <Eigen/Dense>

#include <libwheel/motion_planning/bound_range.hpp>
#include <libwheel/motion_planning/rapidly_exploring_random_trees.hpp>
#include <libwheel/motion_planning/space.hpp>

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

template <>
struct wheel::EuclideanDistance<Eigen::Vector2f> {
    static auto distance(const Eigen::Vector2f &a, const Eigen::Vector2f &b) -> double { return (a - b).norm(); }
};

template <>
struct wheel::Interpolator<Eigen::Vector2f> {
    static auto interpolate(const Eigen::Vector2f &start, const Eigen::Vector2f &stop, std::size_t num_samples)
        -> std::vector<Eigen::Vector2f> {
        std::vector<Eigen::Vector2f> samples;

        const auto step_size = (start - stop) / (num_samples - 1U);
        for (auto i{0U}; i < num_samples; ++i) {
            samples.emplace_back(start + i * step_size);
        }

        return samples;
    }
};

auto print_path(const std::vector<R2Vector> &path, std::ostream &stream = std::cout) -> void {
    for (const auto &point : path) {
        stream << point.transpose().eval() << '\n';
    }
}

auto main() -> int {
    const R2Space space{wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound(5.0)},
                        wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound(5.0)}};

    const auto path = find_path_rrt(space, R2Vector{2, 3}, R2Vector{1, 1});

    if (path.has_value()) {
        std::cout << "Path found!\n";
        std::ofstream filename{"path.txt"};
        print_path(path.value(), filename);
    }

    return 0;
}
