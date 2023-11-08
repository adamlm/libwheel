#include <libwheel/motion_planning/type_traits.hpp>

#include <type_traits>

struct S {};

template <>
struct wheel::motion_planning::customization::dimensionality_impl<S> : std::integral_constant<std::size_t, 2U> {};

static_assert(wheel::motion_planning::dimensionality<S>::value == 2U);
static_assert(wheel::motion_planning::dimensionality<S>::value != 5U);

static_assert(wheel::motion_planning::dimensionality_v<S> == 2U);
static_assert(wheel::motion_planning::dimensionality_v<S> != 5U);
