#ifndef LIBWHEEL_MOTION_PLANNING_DEFAULT_BUFFER_TYPE_HPP
#define LIBWHEEL_MOTION_PLANNING_DEFAULT_BUFFER_TYPE_HPP

namespace wheel {

template <typename T>
concept size_defined = [] {
    using std::size;
    return requires(T t) { size(t); };
}();

template <typename T>
concept compile_time_invocable_size =
    size_defined<T> && std::default_initializable<T> && is_compile_time_invocable_lambda([] {
        using std::size;
        size(T{});
    });

template <typename VectorType>
struct default_buffer_type : std::type_identity<std::vector<typename VectorType::value_type>> {};

template <typename VectorType>
    requires compile_time_invocable_size<VectorType>
struct default_buffer_type<VectorType> : std::type_identity<std::array<typename VectorType::value_type, [] {
    using std::size;
    return size(VectorType{});
}()>> {};

template <typename VectorType>
using default_buffer_type_t = typename default_buffer_type<VectorType>::type;

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_DEFAULT_BUFFER_TYPE_HPP
