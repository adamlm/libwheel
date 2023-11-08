#ifndef LIBWHEEL_MOTION_PLANNING_DIMENSIONAL_BOUND_HPP
#define LIBWHEEL_MOTION_PLANNING_DIMENSIONAL_BOUND_HPP

namespace wheel::motion_planning {

struct DimensionalBound {
    double min{0.0};
    double max{0.0};
};

} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_DIMENSIONAL_BOUND_HPP
