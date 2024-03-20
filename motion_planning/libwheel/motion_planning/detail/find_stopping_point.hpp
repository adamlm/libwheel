#ifndef LIBWHEEL_MOTION_PLANNING_DETAIL_FIND_STOPPING_POINT_HPP
#define LIBWHEEL_MOTION_PLANNING_DETAIL_FIND_STOPPING_POINT_HPP

#include <optional>
#include <ranges>
#include <vector>

#include <boost/geometry.hpp>

namespace wheel::motion_planning::detail {

template <std::ranges::input_range Range, typename UnaryPredicate>
constexpr auto find_stopping_point(Range &&r, UnaryPredicate should_stop) noexcept
    -> std::optional<std::ranges::range_value_t<Range>> {
    if (auto const one_past_stop{std::find_if(std::ranges::begin(r), std::ranges::end(r), should_stop)};
        one_past_stop != std::cbegin(r)) {
        return *std::prev(one_past_stop);
    }

    return std::nullopt;
}

} // namespace wheel::motion_planning::detail

#endif // LIBWHEEL_MOTION_PLANNING_DETAIL_FIND_STOPPING_POINT_HPP
