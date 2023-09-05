#include <array>
#include <list>

#include <libwheel/metaprogramming/is_compile_time_invocable_lambda.hpp>

namespace {

// Compile-time test for a lambda that cannot be invoked at compile time.
[[maybe_unused]]
auto runtime_lambda_static_test() -> void {
    const int runtime_var{0};

    // Failure case calls function overload with C-style variadic function parameters, so this is expected.
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    static_assert(!wheel::is_compile_time_invocable_lambda([&runtime_var] { static_cast<void>(runtime_var); }));
}

} // namespace

// Compile-time tests
static_assert(wheel::is_compile_time_invocable_lambda([] {}));

static_assert(wheel::is_compile_time_invocable_lambda([] { static_cast<void>(std::size(std::array<float, 2>{})); }));
static_assert(std::size(std::array<float, 2>{}) == 2);

// Failure case calls function overload with C-style variadic function parameters, so this is expected.
// NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
static_assert(!wheel::is_compile_time_invocable_lambda([] { static_cast<void>(std::size(std::list<int>{})); }));
