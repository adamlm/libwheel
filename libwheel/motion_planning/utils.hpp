#ifndef LIBWHEEL_MOTION_PLANNING_UTILS_HPP
#define LIBWHEEL_MOTION_PLANNING_UTILS_HPP

#include <ostream>

namespace wheel {

template <typename PathType>
auto printPathNodes(const PathType &path, std::ostream &stream = std::cout) {
    for (const auto &config : path) {
        using namespace wheel;
        stream << to_string(config) << '\n';
    }
}

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_UTILS_HPP
