#ifndef LIBWHEEL_METAPROGRAMMING_IS_COMPILE_TIME_INVOCABLE_LAMBDA_HPP
#define LIBWHEEL_METAPROGRAMMING_IS_COMPILE_TIME_INVOCABLE_LAMBDA_HPP

#include <concepts>

namespace wheel {

/**
 * @brief Check if a lambda is invocable at compile time
 *
 * This overload will be removed from the overload set if the lambda is not compile-time invocable.
 *
 * @tparam Lambda Lambda to be evaluated
 * @param[in] 1 Lambda instance to be evaluated (only used for type deduction)
 * @return true
 */
template <typename Lambda>
    requires std::default_initializable<Lambda> && std::invocable<Lambda>
consteval auto is_compile_time_invocable_lambda(Lambda) -> std::enable_if_t<(Lambda{}(), true), bool> {
    return true;
}

/**
 * @brief Check if a lambda is invocable at compile time
 *
 * This overload will be used if the templated one is removed from the overload set.
 *
 * @param[in] 1 Lambda instance to be evaluated (not used)
 * @return false
 */
consteval auto is_compile_time_invocable_lambda(auto) -> bool { return false; }

} // namespace wheel

#endif // LIBWHEEL_METAPROGRAMMING_IS_COMPILE_TIME_INVOCABLE_LAMBDA_HPP
