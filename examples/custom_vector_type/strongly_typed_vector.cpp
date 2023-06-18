#include <iostream>

#include <libwheel/motion_planning/bound_range.hpp>
#include <libwheel/motion_planning/buffer_type_dispatcher.hpp>
#include <libwheel/motion_planning/copy_buffer_data_strategy.hpp>
#include <libwheel/motion_planning/resize_strategy.hpp>
#include <libwheel/motion_planning/sampler.hpp>
#include <libwheel/motion_planning/space.hpp>

#include <libwheel/strongly_typed_matrix/strongly_typed_matrix.hpp>

struct IdxX {};
struct IdxY {};

using RowIdxList = wheel::TypeList<IdxX, IdxY>;
using CustomVector = wheel::StronglyTypedVector<double, RowIdxList, struct Tag>;

template <>
struct wheel::buffer_type_dispatcher<CustomVector> : std::type_identity<std::array<double, 2>> {};

template <>
struct wheel::CopyBufferDataStrategy<CustomVector, std::array<double, 2>> {
    static auto copy(CustomVector &target, const std::array<double, 2> &buffer) -> void {
        target.at<IdxX>() = std::get<0>(buffer);
        target.at<IdxY>() = std::get<1>(buffer);
    }
};

auto main() -> int {
    const wheel::Space<CustomVector> space{wheel::BoundRange{wheel::LowerBound{-5.0}, wheel::UpperBound{5.0}},
                                           wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}}};

    wheel::UniformSampler sampler{space};

    for (auto i{0}; i < 20; ++i) {
        const auto sample{sampler.next_sample()};
        std::cout << sample.at<IdxX>() << ' ' << sample.at<IdxY>() << '\n';
    }

    return 0;
}
