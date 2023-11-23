#ifndef LIBWHEEL_MOTION_PLANNING_ITERATION_COUNT_HPP
#define LIBWHEEL_MOTION_PLANNING_ITERATION_COUNT_HPP

#include <cstdint>

namespace wheel::motion_planning {

struct IterationCount {
    std::size_t count;

    [[nodiscard]]
    friend auto
    operator<=>(IterationCount const &, IterationCount const &) noexcept = default;

    friend auto operator++(IterationCount &iteration_count) noexcept -> IterationCount & {
        ++iteration_count.count;
        return iteration_count;
    }

    friend auto operator++(IterationCount iteration_count, int /* dummy */) noexcept -> IterationCount {
        ++iteration_count;
        return iteration_count;
    }

    friend auto operator--(IterationCount &iteration_count) noexcept -> IterationCount & {
        --iteration_count.count;
        return iteration_count;
    }

    friend auto operator--(IterationCount iteration_count, int /* dummy */) noexcept -> IterationCount {
        --iteration_count;
        return iteration_count;
    }
};
} // namespace wheel::motion_planning

#endif // LIBWHEEL_MOTION_PLANNING_ITERATION_COUNT_HPP
