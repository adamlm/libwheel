#ifndef LIBWHEEL_MOTION_PLANNING_ATTEMPT_COUNT_HPP
#define LIBWHEEL_MOTION_PLANNING_ATTEMPT_COUNT_HPP

#include <cstdint>

namespace wheel::motion_planning {

struct AttemptCount {
    std::size_t attempts;

    [[nodiscard]]
    friend auto
    operator<=>(AttemptCount const &, AttemptCount const &) noexcept = default;

    friend auto operator++(AttemptCount &attempt_count) noexcept -> AttemptCount & {
        ++attempt_count.attempts;
        return attempt_count;
    }

    friend auto operator++(AttemptCount attempt_count, int /* dummy */) noexcept -> AttemptCount {
        ++attempt_count;
        return attempt_count;
    }

    friend auto operator--(AttemptCount &attempt_count) noexcept -> AttemptCount & {
        --attempt_count.attempts;
        return attempt_count;
    }

    friend auto operator--(AttemptCount attempt_count, int /* dummy */) noexcept -> AttemptCount {
        --attempt_count;
        return attempt_count;
    }
};
} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_ATTEMPT_COUNT_HPP
