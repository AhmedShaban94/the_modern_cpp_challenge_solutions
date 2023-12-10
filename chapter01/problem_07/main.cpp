#include <cmath>
#include <iostream>
#include <set>

#include "catch2/catch_test_macros.hpp"

using AmicablePair = std::pair<size_t, size_t>;

size_t sum_proper_divisors(const size_t& number) {
    size_t result = 1;
    for (size_t i = 2; i <= std::sqrt(number); i++) {
        if (number % i == 0)
            result += (i == (number / i)) ? i : (i + number / i);
    }
    return result;
}

std::vector<AmicablePair> getAmicableNumbers(const size_t& limit) {
    std::vector<AmicablePair> amicablePairs{};
    for (size_t number = 4; number < limit; ++number) {
        const auto sum1 = sum_proper_divisors(number);
        if (sum1 < limit) {
            auto sum2 = sum_proper_divisors(sum1);
            if ((sum2 == number) && (number != sum1))
                amicablePairs.emplace_back(number, sum1);
        }
    }
    return amicablePairs;
}

// chapter-1 -> problem7 (amicable numbers)
TEST_CASE("Get amicable numbers up to specific limit", "[amicable_numbers]") {
    std::vector<AmicablePair> expected{
        {220, 284},     {284, 220},     {1184, 1210},   {1210, 1184},
        {2620, 2924},   {2924, 2620},   {5020, 5564},   {5564, 5020},
        {6232, 6368},   {6368, 6232},   {10744, 10856}, {10856, 10744},
        {12285, 14595}, {14595, 12285}, {17296, 18416}, {18416, 17296},
        {66928, 66992}, {66992, 66928}};
    REQUIRE(getAmicableNumbers(70000) == expected);
}