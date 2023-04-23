#ifndef LIBWHEEL_MOTION_PLANNING_TAGGED_VALUE_HPP
#define LIBWHEEL_MOTION_PLANNING_TAGGED_VALUE_HPP

namespace wheel {

/**
 * @brief This class wraps a primitive or user-defined type and associates it
 * with a semantic tag.
 *
 * This class structure is based on Jonathan Boccara's blog series on strong
 * types: https://www.fluentcpp.com/2016/12/05/named-constructors/.
 *
 * @tparam StorageType The underlying type being wrapped
 * @tparam Tag The semantic tag associated with the wrapped type. (This is a
 * phantom type.)
 */
template <typename StorageType, typename Tag>
class TaggedValue {
  public:

    /**
     * @brief Construct a new TaggedValue object
     *
     * @param value Value of the underlying type being wrapped
     */
    explicit TaggedValue(StorageType value) : value_{value} {}

    /**
     * @brief Get a mutable reference to the wrapped type
     *
     * @return StorageType& Mutable reference to wrapped type
     */
    auto get() noexcept -> StorageType & { return value_; }

    /**
     * @brief Get an immutable reference to the wrapped type
     *
     * @return const StorageType& Immutable reference to wrapped type
     */
    auto get() const noexcept -> const StorageType & { return value_; }

  private:
    StorageType value_;
};

} // namespace wheel

#endif // LIBWHEEL_MOTION_PLANNING_TAGGED_VALUE_HPP
