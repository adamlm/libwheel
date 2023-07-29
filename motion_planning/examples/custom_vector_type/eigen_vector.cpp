#include <array>
#include <iostream>

#include <libwheel/motion_planning/bound_range.hpp>
#include <libwheel/motion_planning/buffer_type_dispatcher.hpp>
#include <libwheel/motion_planning/copy_buffer_data_strategy.hpp>
#include <libwheel/motion_planning/resize_strategy.hpp>
#include <libwheel/motion_planning/sampler.hpp>
#include <libwheel/motion_planning/space.hpp>

#include <Eigen/Dense>

using CustomVector = Eigen::Vector3f;
using CustomSpace = wheel::Space<CustomVector>;

template <typename Derived>
    requires std::is_base_of_v<Eigen::MatrixBase<Derived>, Derived>
struct wheel::buffer_type_dispatcher<Derived>
    : std::type_identity<std::array<typename Derived::Scalar, Derived::RowsAtCompileTime>> {};

template <typename Derived>
    requires std::is_base_of_v<Eigen::MatrixBase<Derived>, Derived>
struct wheel::ResizeStrategy<Derived> {
    static auto resize(Derived &, std::size_t) -> void {}
};

template <>
struct wheel::CopyBufferDataStrategy<CustomVector, std::array<float, 3>> {
    static auto copy(CustomVector &target, const std::array<float, 3> &buffer) -> void {
        target(0) = std::get<0>(buffer);
        target(1) = std::get<1>(buffer);
        target(2) = std::get<2>(buffer);
    }
};

int main() {
    const CustomSpace space{wheel::BoundRange{wheel::LowerBound{-5.0}, wheel::UpperBound{5.0}},
                            wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}},
                            wheel::BoundRange{wheel::LowerBound{20.0}, wheel::UpperBound{30.0}}};

    wheel::UniformSampler<CustomSpace> sampler{space};

    for (auto i{0}; i < 20; ++i) {
        const auto sample{sampler.next_sample()};
        std::cout << sample.transpose() << '\n';
    }

    return 0;
}
