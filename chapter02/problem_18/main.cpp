#include "catch2/catch.hpp"
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <type_traits>

template <typename Predicate, typename... Args>
auto minimum(Predicate pred, Args... args)
{
    using T = std::common_type_t<Args...>;
    const std::array<T, sizeof...(args)> arr{args...};
    return *std::min_element(arr.begin(), arr.end(), pred);
}

TEST_CASE("testing minimum function with any number of arguments", "[mini_variadic]")
{
    SECTION("Testing integral types")
    {
        REQUIRE(1 == minimum(std::less<>(), 1, 2, 3, 4, 5));
        REQUIRE(-10 == minimum(std::less<>(), -1, -2, -10, 18, 20, 19));
    }

    SECTION("testing floating-point types")
    {
        REQUIRE(1.5 == minimum(std::less<>(), 1.6, 1.5, 2.5, 3.5, 5.5));
        REQUIRE(1.0 == minimum(std::less<>(), 1.0, 2.0, 3.0, 4.0, 5.0));
    }
}