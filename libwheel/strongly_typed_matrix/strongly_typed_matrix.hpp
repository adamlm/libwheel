#ifndef LIBWHEEL_STRONGLY_TYPED_MATRIX_STRONGLY_TYPED_MATRIX_HPP
#define LIBWHEEL_STRONGLY_TYPED_MATRIX_STRONGLY_TYPED_MATRIX_HPP

// Standard library includes
#include <concepts>
#include <type_traits>

// Third-party includes
#include <Eigen/Dense>
#include <libwheel/metaprogramming/type_list.hpp>

namespace wheel {

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

    template <typename... ScalarTs>
    StronglyTypedMatrix(ScalarTs... scalars) {
        std::array<ScalarType, RowIdxList::size * ColIdxList::size> buffer{scalars...};

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
