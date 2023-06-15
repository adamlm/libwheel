#ifndef LIBWHEEL_MOTION_PLANNING_COPY_BUFFER_DATA_STRATEGY_HPP
#define LIBWHEEL_MOTION_PLANNING_COPY_BUFFER_DATA_STRATEGY_HPP

namespace wheel {

template <typename VectorType, typename BufferType>
struct CopyBufferDataStrategy {
    static auto copy(VectorType &destination, const BufferType &buffer)
        -> std::enable_if_t<std::same_as<VectorType, BufferType>> {
        destination = buffer;
    }
};

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_COPY_BUFFER_DATA_STRATEGY_HPP
