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
    [[nodiscard]] auto get() const -> decltype(auto) {
        return std::get<wheel::index_of_v<IndexType, wheel::TypeList<IndexTs...>>>(data_);
    }

    template <typename IndexType>
    [[nodiscard]] auto get() -> decltype(auto) {
        return std::get<wheel::index_of_v<IndexType, wheel::TypeList<IndexTs...>>>(data_);
    }

  private:
    std::tuple<StorageTs...> data_;
};

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

template <std::default_initializable VectorType, typename DistributionType,
          typename RandomDeviceType = std::random_device, typename RandomEngineType = std::default_random_engine>
auto make_random_vector(std::array<DistributionType, VectorType::size> &distributions) -> VectorType {
    VectorType vector;

    RandomDeviceType device;
    RandomEngineType engine{device()};

    make_random_vector_impl<wheel::begin_type_t<typename VectorType::IndexTypeList>>(vector, engine, distributions);

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

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_VECTOR_HPP
