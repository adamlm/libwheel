#include <fstream>
#include <iostream>

#include <libwheel/motion_planning/bound_range.hpp>
#include <libwheel/motion_planning/r2_space.hpp>
#include <libwheel/motion_planning/rapidly_exploring_random_trees.hpp>
#include <libwheel/motion_planning/sampler.hpp>
#include <libwheel/motion_planning/utils.hpp>

auto main() -> int {
    const wheel::R2Space space{wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound(5.0)},
                               wheel::BoundRange{wheel::LowerBound{0.0}, wheel::UpperBound(5.0)}};

    wheel::UniformSampler sampler{space};

    const auto path = wheel::findRrtPath(sampler, wheel::R2Vector{2, 3}, wheel::R2Vector{1, 1});

    if (path.has_value()) {
        std::cout << "Path found!\n";
        std::ofstream filename{"path.txt"};

        wheel::printPathNodes(path.value(), filename);
    }

    return 0;
}
