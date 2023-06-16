#include <array>
#include <list>
#include <vector>

#include <libwheel/metaprogramming/is_compile_time_invocable_lambda.hpp>

// Compile-time test for a lambda that cannot be invoked at compile time
auto runtime_lambda_static_test() -> void {
    const int runtime_var{0};

    static_assert(!wheel::is_compile_time_invocable_lambda([&runtime_var] { static_cast<void>(runtime_var); }));
}

// Compile-time tests
static_assert(wheel::is_compile_time_invocable_lambda([] {}));

static_assert(wheel::is_compile_time_invocable_lambda([] { std::size(std::array<float, 2>{}); }));
static_assert(std::size(std::array<float, 2>{}) == 2);

static_assert(!wheel::is_compile_time_invocable_lambda([] { std::size(std::list<int>{}); }));
