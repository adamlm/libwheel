#ifndef LIBWHEEL_STRONGLY_TYPED_MATRIX_STRONGLY_TYPED_MATRIX_HPP
#define LIBWHEEL_STRONGLY_TYPED_MATRIX_STRONGLY_TYPED_MATRIX_HPP

// Standard library headers
#include <concepts>
#include <type_traits>

// Third-party headers
#include <Eigen/Dense>
#include <libwheel/metaprogramming/type_list.hpp>

// Local library headers
#include "index_types.hpp"
#include "strongly_typed_coefficient.hpp"

namespace wheel {

namespace detail {

template <typename RowIdxList, typename ColIdxList, typename... Coefficients>
concept compatible_coefficient_count = sizeof...(Coefficients) == (RowIdxList::size * ColIdxList::size);

template <typename RowIdxList, typename ColIdxList, std::size_t index, typename Coefficient, typename... Coefficients>
constexpr auto are_coefficient_types_compatible() -> bool {
    constexpr auto expected_row_index = index / ColIdxList::size;
    constexpr auto actual_row_index = index_of_v<typename Coefficient::row_index_type, RowIdxList>;

    constexpr auto expected_col_index = index % ColIdxList::size;
    constexpr auto actual_col_index = index_of_v<typename Coefficient::column_index_type, ColIdxList>;

    constexpr auto is_current_coeff_compatible =
        expected_row_index == actual_row_index && expected_col_index == actual_col_index;

    if constexpr (index < RowIdxList::size * ColIdxList::size - 1) {
        return is_current_coeff_compatible &&
               are_coefficient_types_compatible<RowIdxList, ColIdxList, index + 1, Coefficients...>();
    }

    return is_current_coeff_compatible;
}

template <typename RowIdxList, typename ColIdxList, typename... Coefficients>
concept compatible_coefficient_types = are_coefficient_types_compatible<RowIdxList, ColIdxList, 0, Coefficients...>();

} // namespace detail

/**
 * @brief A strongly-typed wrapper around a matrix type
 *
 * @tparam ScalarType Underlying storage type for matrix elements
 * @tparam RowIdxList List of index `struct`s associated with row elements
 * @tparam ColIdxList List of index `struct`s associated with column elements
 * @tparam SemanticTag A tag `struct` to indicate matrix's semantic purpose
 */
template <typename ScalarType, typename RowIdxList, typename ColIdxList, typename SemanticTag>
    requires(std::is_arithmetic_v<ScalarType> && RowIdxList::size > 0 && ColIdxList::size > 0)
class StronglyTypedMatrix {
  public:
    using raw_matrix_type = Eigen::Matrix<ScalarType, RowIdxList::size, ColIdxList::size>;
    using size_type = std::size_t;

    static constexpr size_type size{raw_matrix_type::SizeAtCompileTime};

    StronglyTypedMatrix() : raw_matrix_(raw_matrix_type::Zero()) {}

    template <typename... ScalarTs>
        requires detail::compatible_coefficient_count<RowIdxList, ColIdxList, ScalarTs...> &&
                 detail::compatible_coefficient_types<RowIdxList, ColIdxList, ScalarTs...>
    StronglyTypedMatrix(ScalarTs... scalars) {
        std::array<ScalarType, RowIdxList::size * ColIdxList::size> buffer{scalars.raw_value()...};

        if constexpr (RowIdxList::size == 1 || ColIdxList::size == 1) {
            raw_matrix_ = Eigen::Map<raw_matrix_type>(buffer.data());
        } else {
            // Data will come in row-major ordering, but Eigen uses column-major ordering, so we need to transpose
            // before storing the results. This is not an issue for vectors because there is only one dimension
            // to worry about.
            raw_matrix_ = Eigen::Map<raw_matrix_type>(buffer.data()).transpose();
        }
    }

    /**
     * @brief Access the underlying matrix without type safety
     *
     * @return Const reference to underlying matrix
     */
    [[nodiscard]]
    auto raw_matrix() const noexcept -> const raw_matrix_type & {
        return raw_matrix_;
    }

    /**
     * @brief Access the underlying matrix without type safety
     *
     * @return Mutable reference to underlying matrix
     */
    [[nodiscard]]
    auto raw_matrix() noexcept -> raw_matrix_type & {
        return raw_matrix_;
    }

    /**
     * @brief Get the element value at the specified indices
     *
     * @tparam RowIdxType Index `struct` associated with element's row
     * @tparam ColIdxType Index `struct` associated with element's column
     * @return Copy of the element value
     */
    template <typename RowIdxType, typename ColIdxType>
        requires(ColIdxList::size > 1)
    [[nodiscard]]
    auto at() const noexcept -> ScalarType {
        return raw_matrix_(index_of_v<RowIdxType, RowIdxList>, index_of_v<ColIdxType, ColIdxList>);
    }

    /**
     * @brief Get the element value at the specified index
     *
     * @tparam RowIdxType Index `struct` associated with element's row
     * @return Copy of the element value
     */
    template <typename RowIdxType>
        requires(ColIdxList::size == 1)
    [[nodiscard]]
    auto at() const noexcept -> ScalarType {
        return raw_matrix_(index_of_v<RowIdxType, RowIdxList>);
    }

    /**
     * @brief Access the element at the specified indices
     *
     * @tparam RowIdxType Index `struct` associated with element's row
     * @tparam ColIdxType Index `struct` associated with element's column
     * @return Mutable reference to element value
     */
    template <typename RowIdxType, typename ColIdxType>
        requires(ColIdxList::size > 1)
    [[nodiscard]]
    auto at() noexcept -> ScalarType & {
        return raw_matrix_(index_of_v<RowIdxType, RowIdxList>, index_of_v<ColIdxType, ColIdxList>);
    }

    /**
     * @brief Access the element at the specified index
     *
     * @tparam RowIdxType Index `struct` associated with element's row
     * @return Mutable reference to element value
     */
    template <typename RowIdxType>
        requires(ColIdxList::size == 1)
    [[nodiscard]]
    auto at() noexcept -> ScalarType & {
        return raw_matrix_(index_of_v<RowIdxType, RowIdxList>);
    }

  private:
    raw_matrix_type raw_matrix_;
};

/**
 * @brief A strongly-typed column vector
 *
 * @tparam ScalarType Underlying storage type for vector elements
 * @tparam RowIdxList List of index `struct`s associated with row elements
 * @tparam SemanticTag A tag `struct` to indicate vector's semantic purpose
 */
template <typename ScalarType, typename RowIdxList, typename SemanticTag>
using StronglyTypedVector = StronglyTypedMatrix<ScalarType, RowIdxList, TypeList<NoIdxType>, SemanticTag>;

} // namespace wheel

#endif // LIBWHEEL_STRONGLY_TYPED_MATRIX_STRONGLY_TYPED_MATRIX_HPP
