#ifndef LIBWHEEL_MOTION_PLANNING_VECTOR_HPP
#define LIBWHEEL_MOTION_PLANNING_VECTOR_HPP

#include <concepts>
#include <random>
#include <tuple>

#include <libwheel/metaprogramming/type_list.hpp>

namespace wheel {

template <typename... IndexTypes>
using IndexTypeList = typename wheel::TypeList<IndexTypes...>;

template <typename... StorageTypes>
using StorageTypeList = typename wheel::TypeList<StorageTypes...>;

template <typename, typename>
class Vector;

template <typename... IndexTs, typename... StorageTs>
    requires(sizeof...(IndexTs) == sizeof...(StorageTs))
class Vector<IndexTypeList<IndexTs...>, StorageTypeList<StorageTs...>> {
  public:
    using IndexTypeList = wheel::TypeList<IndexTs...>;
    using StorageTypeList = wheel::TypeList<StorageTs...>;
    static constexpr auto size = IndexTypeList::size;

    explicit Vector() = default;

    explicit Vector(StorageTs... elements) : data_{elements...} {}

    template <typename IndexType>
    [[nodiscard]]
    auto get() const -> decltype(auto) {
        return std::get<wheel::index_of_v<IndexType, wheel::TypeList<IndexTs...>>>(data_);
    }

    template <typename IndexType>
    [[nodiscard]]
    auto get() -> decltype(auto) {
        return std::get<wheel::index_of_v<IndexType, wheel::TypeList<IndexTs...>>>(data_);
    }

  private:
    std::tuple<StorageTs...> data_;
};

namespace detail {

template <typename CurrentIndex, typename VectorType, template <typename> typename RelationType>
auto apply_binary_function_impl(const VectorType &lhs, const VectorType &rhs, VectorType &result) {
    using IndexTypeList = typename VectorType::IndexTypeList;

    result.template get<CurrentIndex>() =
        RelationType{}(lhs.template get<CurrentIndex>(), rhs.template get<CurrentIndex>());

    if constexpr (wheel::has_next_type<CurrentIndex, IndexTypeList>) {
        apply_binary_function_impl<wheel::next_type_t<CurrentIndex, IndexTypeList>, VectorType, RelationType>(lhs, rhs,
                                                                                                              result);
    }
}

template <typename CurrentIndex, typename VectorType, typename ScalarType, template <typename> typename RelationType>
    requires(!std::same_as<VectorType, ScalarType>)
auto apply_binary_function_impl(const VectorType &lhs, const ScalarType &rhs, VectorType &result) {
    using IndexTypeList = typename VectorType::IndexTypeList;

    result.template get<CurrentIndex>() =
        RelationType{}(lhs.template get<CurrentIndex>(), static_cast<decltype(lhs.template get<CurrentIndex>())>(rhs));

    if constexpr (wheel::has_next_type<CurrentIndex, IndexTypeList>) {
        apply_binary_function_impl<wheel::next_type_t<CurrentIndex, IndexTypeList>, VectorType, ScalarType,
                                   RelationType>(lhs, rhs, result);
    }
}

} // namespace detail

template <typename VectorType, template <typename> typename RelationType>
auto apply_binary_function(const VectorType &lhs, const VectorType &rhs) -> VectorType {
    using IndexTypeList = typename VectorType::IndexTypeList;

    VectorType result;

    detail::apply_binary_function_impl<wheel::begin_type_t<IndexTypeList>, VectorType, RelationType>(lhs, rhs, result);

    return result;
}

template <typename VectorType, typename ScalarType, template <typename> typename RelationType>
    requires(!std::same_as<VectorType, ScalarType>)
auto apply_binary_function(const VectorType &lhs, const ScalarType &rhs) -> VectorType {
    using IndexTypeList = typename VectorType::IndexTypeList;

    VectorType result;

    detail::apply_binary_function_impl<wheel::begin_type_t<IndexTypeList>, VectorType, ScalarType, RelationType>(
        lhs, rhs, result);

    return result;
}

namespace detail {

template <typename CurrentIndex, typename VectorType, template <typename> typename RelationType>
auto apply_comparison_impl(const VectorType &lhs, const VectorType &rhs) -> bool {
    using IndexTypeList = typename VectorType::IndexTypeList;

    auto result = RelationType{}(lhs.template get<CurrentIndex>(), rhs.template get<CurrentIndex>());

    if constexpr (wheel::has_next_type<CurrentIndex, IndexTypeList>) {
        result &&apply_comparison_impl<wheel::next_type_t<CurrentIndex, IndexTypeList>, VectorType, RelationType>(lhs,
                                                                                                                  rhs);
    }

    return result;
}

} // namespace detail

template <typename VectorType, template <typename> typename RelationType>
auto apply_comparison(const VectorType &lhs, const VectorType &rhs) -> bool {
    using IndexTypeList = typename VectorType::IndexTypeList;

    return detail::apply_comparison_impl<wheel::begin_type_t<IndexTypeList>, VectorType, RelationType>(lhs, rhs);
}

template <typename VectorType>
auto operator==(const VectorType &lhs, const VectorType &rhs) -> bool {
    return apply_comparison<VectorType, std::equal_to>(lhs, rhs);
}

template <typename VectorType>
auto operator+=(VectorType &lhs, const VectorType &rhs) -> VectorType & {
    lhs = apply_binary_function<VectorType, std::plus>(lhs, rhs);

    return lhs;
}

template <typename VectorType>
auto operator-=(VectorType &lhs, const VectorType &rhs) -> VectorType & {
    lhs = apply_binary_function<VectorType, std::minus>(lhs, rhs);

    return lhs;
}

template <typename ScalarType, typename VectorType>
auto operator*=(VectorType &lhs, ScalarType rhs) -> VectorType & {
    lhs = apply_binary_function<VectorType, ScalarType, std::multiplies>(lhs, rhs);

    return lhs;
}

template <typename ScalarType, typename VectorType>
auto operator/=(VectorType &lhs, ScalarType rhs) -> VectorType & {
    lhs = apply_binary_function<VectorType, ScalarType, std::divides>(lhs, rhs);

    return lhs;
}

template <typename VectorType>
auto operator+(VectorType lhs, const VectorType &rhs) -> VectorType {
    return lhs += rhs;
}

template <typename VectorType>
auto operator-(VectorType lhs, const VectorType &rhs) -> VectorType {
    return lhs -= rhs;
}

template <typename ScalarType, typename VectorType>
auto operator*(ScalarType lhs, VectorType rhs) -> VectorType {
    return rhs *= lhs;
}

template <typename ScalarType, typename VectorType>
    requires(std::integral<ScalarType> or std::floating_point<ScalarType>)
auto operator*(VectorType lhs, ScalarType rhs) -> VectorType {
    return lhs *= rhs;
}

template <typename ScalarType, typename VectorType>
    requires(std::integral<ScalarType> or std::floating_point<ScalarType>)
auto operator/(VectorType lhs, ScalarType rhs) -> VectorType {
    return lhs /= rhs;
}

namespace detail {

template <typename CurrentIndex, typename VectorType>
auto make_random_vector_impl(VectorType &vector, auto &engine, auto &distributions) -> void {
    using IndexTypeList = typename VectorType::IndexTypeList;

    const auto value{std::get<wheel::index_of_v<CurrentIndex, IndexTypeList>>(distributions)(engine)};

    vector.template get<CurrentIndex>() =
        static_cast<std::remove_cvref_t<decltype(vector.template get<CurrentIndex>())>>(value);

    if constexpr (wheel::has_next_type<CurrentIndex, IndexTypeList>) {
        make_random_vector_impl<wheel::next_type_t<CurrentIndex, IndexTypeList>>(vector, engine, distributions);
    }
}

} // namespace detail

template <std::default_initializable VectorType, typename DistributionType,
          typename RandomDeviceType = std::random_device, typename RandomEngineType = std::default_random_engine>
auto make_random_vector(std::array<DistributionType, VectorType::size> &distributions) -> VectorType {
    VectorType vector;

    RandomDeviceType device;
    RandomEngineType engine{device()};

    detail::make_random_vector_impl<wheel::begin_type_t<typename VectorType::IndexTypeList>>(vector, engine,
                                                                                             distributions);

    return vector;
}

namespace detail {

template <typename CurrentIndex, typename VectorType>
auto to_string_impl(const VectorType &vector, std::string &string, char delimiter) -> void {
    using IndexTypeList = typename VectorType::IndexTypeList;

    string.append(std::to_string(vector.template get<CurrentIndex>()));

    if constexpr (wheel::has_next_type<CurrentIndex, IndexTypeList>) {
        string.push_back(delimiter);
        to_string_impl<wheel::next_type_t<CurrentIndex, IndexTypeList>>(vector, string, delimiter);
    }
}

} // namespace detail

template <typename VectorType>
auto to_string(VectorType vector, char delimiter = ' ') -> std::string {
    std::string string;

    detail::to_string_impl<wheel::begin_type_t<typename VectorType::IndexTypeList>>(vector, string, delimiter);

    return string;
}

namespace detail {

template <typename CurrentIndex, typename VectorType>
auto euclidean_distance_impl(const VectorType &source, const VectorType &target) -> double {
    using IndexTypeList = typename VectorType::IndexTypeList;

    double result = std::abs(static_cast<double>(source.template get<CurrentIndex>()) -
                             static_cast<double>(target.template get<CurrentIndex>()));
    result = std::pow(result, 2);

    if constexpr (wheel::has_next_type<CurrentIndex, IndexTypeList>) {
        result += euclidean_distance_impl<wheel::next_type_t<CurrentIndex, IndexTypeList>>(source, target);
    }

    return result;
}

} // namespace detail

template <typename VectorType>
auto euclidean_distance(const VectorType &source, const VectorType &target) -> double {
    const auto sum_of_squares =
        detail::euclidean_distance_impl<wheel::begin_type_t<typename VectorType::IndexTypeList>>(source, target);

    return std::sqrt(sum_of_squares);
}

template <typename VectorType>
auto interpolate(const VectorType &source, const VectorType &target, std::size_t num_samples)
    -> std::vector<VectorType> {
    std::vector<VectorType> vectors;
    vectors.reserve(num_samples);

    const auto step_vector = (target - source) / (num_samples - 1U);

    for (auto i{0U}; i < num_samples; ++i) {
        vectors.push_back(source + i * step_vector);
    }

    return vectors;
}

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_VECTOR_HPP
