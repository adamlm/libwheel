#ifndef LIBWHEEL_MOTION_PLANNING_R2_SPACE_HPP
#define LIBWHEEL_MOTION_PLANNING_R2_SPACE_HPP

#include "libwheel/motion_planning/space.hpp"
#include "libwheel/motion_planning/vector.hpp"

namespace wheel {

struct X {};
struct Y {};

/**
 * @brief Vector representing a point in two-dimensional space
 */
using R2Vector = wheel::Vector<wheel::IndexTypeList<X, Y>, wheel::StorageTypeList<float, float>>;

/**
 * @brief The two-dimensional Euclidean space (R^2)
 */
using R2Space = Space<R2Vector>;

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_R2_SPACE_HPP
