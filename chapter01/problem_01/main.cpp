#include "catch2/catch.hpp"
#include "iostream"
#include <numeric>
#include <vector>

std::size_t sumOfDivisibleNumbers(const std::size_t& limit)
{
    std::vector<std::size_t> vec{};

    for (std::size_t i = 3; i <= limit; ++i)
        if (i % 3 == 0 or i % 5 == 0)
            vec.emplace_back(i);

    return std::accumulate(vec.begin(), vec.end(), static_cast<std::size_t>(0));
}

// Chapter-1 -> problem 1  (sum of divisible numbers on 3 or 5)
TEST_CASE("Get sum of divisible numbers", "[sum_of_divisible_numbers]")
{
    REQUIRE(sumOfDivisibleNumbers(10) == 33);
    REQUIRE(sumOfDivisibleNumbers(15) == 60);
    REQUIRE(sumOfDivisibleNumbers(22) == 119);
    REQUIRE(sumOfDivisibleNumbers(35) == 293);
    REQUIRE(sumOfDivisibleNumbers(50) == 593);
    REQUIRE(sumOfDivisibleNumbers(100) == 2418);
}