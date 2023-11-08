#ifndef LIBWHEEL_MOTION_PLANNING_ORTHOTOPE_HPP
#define LIBWHEEL_MOTION_PLANNING_ORTHOTOPE_HPP

#include <cstdint>

#include "libwheel/motion_planning/dimensional_bound.hpp"

namespace wheel::motion_planning {

template <std::size_t Dimensionality>
struct Orthotope {
    std::array<DimensionalBound, Dimensionality> bounds{};
};

namespace customization {

template <typename T>
struct do_axis_aligned_bounding_orthotope {};

} // namespace customization

inline constexpr auto axis_aligned_bounding_orthotope = [](auto &&space) {
    return customization::do_axis_aligned_bounding_orthotope<std::remove_cvref_t<decltype(space)>>::_(
        std::forward<decltype(space)>(space));
};

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_ORTHOTOPE_HPP
