#include <iostream>

#include <libwheel/motion_planning/bound_range.hpp>
#include <libwheel/motion_planning/buffer_type_dispatcher.hpp>
#include <libwheel/motion_planning/copy_buffer_data_strategy.hpp>
#include <libwheel/motion_planning/resize_strategy.hpp>
#include <libwheel/motion_planning/sampler.hpp>
#include <libwheel/motion_planning/space.hpp>

struct Point3d {
    using value_type = float;

    value_type x;
    value_type y;
    value_type z;
};

constexpr auto size(const Point3d &) noexcept -> std::size_t { return 3; }

template <>
struct wheel::CopyBufferDataStrategy<Point3d, std::array<float, 3>> {
    static auto copy(Point3d &point, const std::array<float, 3> &buffer) -> void {
        point.x = std::get<0>(buffer);
        point.y = std::get<1>(buffer);
        point.z = std::get<2>(buffer);
    }
};

auto print_point(const Point3d &point) { std::cout << point.x << ' ' << point.y << ' ' << point.z << '\n'; }

int main() {
    const wheel::Space<Point3d> space{wheel::BoundRange{wheel::LowerBound{-5.0}, wheel::UpperBound{5.0}},
                                      wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}},
                                      wheel::BoundRange{wheel::LowerBound{20.0}, wheel::UpperBound{30.0}}};

    wheel::UniformSampler sampler{space};

    for (auto i{0}; i < 20; ++i) {
        const auto sample{sampler.next_sample()};
        print_point(sample);
    }

    return 0;
}
