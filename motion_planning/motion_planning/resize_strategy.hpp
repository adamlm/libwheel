#ifndef LIBWHEEL_MOTION_PLANNING_RESIZE_STRATEGY_HPP
#define LIBWHEEL_MOTION_PLANNING_RESIZE_STRATEGY_HPP

#include <cstddef>

namespace wheel {

template <typename T>
concept resizable = requires(T t, std::size_t s) { t.resize(s); };

template <typename VectorType>
struct ResizeStrategy {
    static auto resize(VectorType &vector, std::size_t new_size) -> void {
        if constexpr (resizable<VectorType>) {
            vector.resize(new_size);
        }
    }
};

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_RESIZE_STRATEGY_HPP
