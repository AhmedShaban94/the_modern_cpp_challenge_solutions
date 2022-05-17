#include "catch2/catch.hpp"
#include "iostream"
#include <numeric>
#include <vector>

std::size_t sumOfDivisableNumbers(const std::size_t& limit)
{
    std::vector<std::size_t> vec{};

    for (std::size_t i = 3; i <= limit; ++i)
        if (i % 3 == 0 or i % 5 == 0)
            vec.emplace_back(i);

    return std::accumulate(vec.begin(), vec.end(), static_cast<std::size_t>(0));
}

// Chapter-1 -> problem 1  (sum of divisable numbers on 3 or 5)
TEST_CASE("Count days between two dates", "[days_between_two_dates]")
{
    REQUIRE(sumOfDivisableNumbers(10) == 33);
    REQUIRE(sumOfDivisableNumbers(15) == 60);
    REQUIRE(sumOfDivisableNumbers(22) == 119);
    REQUIRE(sumOfDivisableNumbers(35) == 293);
    REQUIRE(sumOfDivisableNumbers(50) == 593);
    REQUIRE(sumOfDivisableNumbers(100) == 2418);
}