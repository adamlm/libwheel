#ifndef LIBWHEEL_STRONGLY_TYPED_MATRIX_STRONGLY_TYPED_COEFFICIENT_HPP
#define LIBWHEEL_STRONGLY_TYPED_MATRIX_STRONGLY_TYPED_COEFFICIENT_HPP

// Standard library headers
#include <type_traits>

// Local library headers
#include "index_types.hpp"

namespace wheel {

template <typename ScalarType, typename RowIdxType, typename ColIdxType = NoIdxType>
    requires std::is_arithmetic_v<ScalarType>
class StronglyTypedCoefficient {
  public:
    using row_index_type = RowIdxType;
    using column_index_type = ColIdxType;

    explicit StronglyTypedCoefficient(ScalarType value) noexcept : value_{value} {}

    auto raw_value() const noexcept -> ScalarType { return value_; }

  private:
    ScalarType value_;
};

template <typename RowIdxType, typename ColIdxType, typename ScalarType>
    requires std::is_arithmetic_v<ScalarType>
auto wrap_raw_value(ScalarType value) {
    return StronglyTypedCoefficient<ScalarType, RowIdxType, ColIdxType>{value};
}

template <typename RowIdxType, typename ScalarType>
    requires std::is_arithmetic_v<ScalarType>
auto wrap_raw_value(ScalarType value) {
    return wrap_raw_value<RowIdxType, NoIdxType, ScalarType>(value);
}

} // namespace wheel

#endif // LIBWHEEL_STRONGLY_TYPED_MATRIX_STRONGLY_TYPED_COEFFICIENT_HPP
