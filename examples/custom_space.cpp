#include <array>
#include <fstream>
#include <iostream>

#include <libwheel/motion_planning/bound_range.hpp>
#include <libwheel/motion_planning/sampler.hpp>
#include <libwheel/motion_planning/space.hpp>
#include <libwheel/motion_planning/vector.hpp>

struct Foo {};
struct Bar {};
struct Baz {};

using CustomVector = wheel::Vector<wheel::IndexTypeList<Foo, Bar, Baz>, wheel::StorageTypeList<double, double, double>>;

using CustomSpace = wheel::Space<CustomVector>;

auto array_to_vector_type(const std::array<double, 3> &input, CustomVector &output) -> void {
    output.get<Foo>() = std::get<0>(input);
    output.get<Bar>() = std::get<1>(input);
    output.get<Baz>() = std::get<2>(input);
}

int main() {
    CustomSpace space{wheel::BoundRange{wheel::LowerBound{-5.0}, wheel::UpperBound{5.0}},
                      wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound{1.0}},
                      wheel::BoundRange{wheel::LowerBound{20.0}, wheel::UpperBound{30.0}}};

    wheel::UniformSampler sampler{space};

    for (auto i{0}; i < 20; ++i) {
        const auto sample{sampler.nextSample()};
        std::cout << wheel::to_string(sample) << '\n';
    }

    return 0;
}
