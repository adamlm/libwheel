#ifndef LIBWHEEL_MOTION_PLANNING_UTILS_HPP
#define LIBWHEEL_MOTION_PLANNING_UTILS_HPP

#include <ostream>

namespace wheel {

template <typename PathType>
auto printPathNodes(const PathType &path, std::ostream &stream = std::cout) {
    using VectorType = typename PathType::value_type;
    for (const auto& config : path) {
        stream << VectorType::toString(config) << '\n';
    }
}

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_UTILS_HPP
