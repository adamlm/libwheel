#ifndef LIBWHEEL_MOTION_PLANNING_BUFFER_TYPE_DISPATCHER_HPP
#define LIBWHEEL_MOTION_PLANNING_BUFFER_TYPE_DISPATCHER_HPP

#include <libwheel/motion_planning/default_buffer_type.hpp>

namespace wheel {

template <typename VectorType>
struct buffer_type_dispatcher : default_buffer_type<VectorType> {};

template <typename VectorType>
using buffer_type_dispatcher_t = typename buffer_type_dispatcher<VectorType>::type;

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_BUFFER_TYPE_DISPATCHER_HPP
