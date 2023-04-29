#ifndef LIBWHEEL_ANGLE_ANGLE_HPP
#define LIBWHEEL_ANGLE_ANGLE_HPP

#include <complex>
#include <concepts>

namespace wheel {

template <std::floating_point StorageType>
class AngleDisplacement;

template <std::floating_point StorageType>
class Angle {
  public:
    explicit Angle(StorageType value) noexcept : value_{std::polar(static_cast<StorageType>(1.0), value)} {}

    [[nodiscard]] auto getValue() const noexcept -> StorageType {
        auto value{std::arg(value_)};

        if (value < static_cast<StorageType>(0.0)) {
            value += 2 * static_cast<StorageType>(std::numbers::pi);
        }

        return value;
    }

    auto setValue(StorageType value) noexcept { value_ = std::polar(static_cast<StorageType>(1.0), value); }

  private:
    friend AngleDisplacement<StorageType>;

    std::complex<StorageType> value_;
};

template <std::floating_point StorageType>
class AngleDisplacement {
  public:
    explicit AngleDisplacement(const Angle<StorageType> &lhs, const Angle<StorageType> &rhs) noexcept
        : value_{std::arg(rhs.value_ / lhs.value_)} {}

    [[nodiscard]] auto getValue() const noexcept -> StorageType { return value_; }

  private:
    StorageType value_;
};

template <std::floating_point StorageType>
[[nodiscard]] inline auto displacement(const Angle<StorageType> &lhs, const Angle<StorageType> &rhs) {
    return AngleDisplacement<StorageType>{lhs, rhs};
}

} // namespace wheel

#endif // LIBWHEEL_ANGLE_ANGLE_HPP
