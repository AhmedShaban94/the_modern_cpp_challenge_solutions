#include <iostream>
#include <numeric>
#include <vector>

#include "catch2/catch_test_macros.hpp"

using PairsVector = std::vector<std::pair<int, int>>;
PairsVector abundantNumbers(const std::size_t& limit) {
    std::vector<std::size_t> divisors{};
    PairsVector nums{};
    for (std::size_t i = 1; i < limit; ++i) {
        for (std::size_t j = 1; j < i; ++j) {
            if (i % j == 0)
                divisors.push_back(j);
        }
        auto divisors_sum =
            std::accumulate(divisors.begin(), divisors.end(), (std::size_t)0);
        if (divisors_sum > i)
            nums.emplace_back(i, divisors_sum - i);
        divisors.clear();
    }
    return nums;
}

// chapter-1 -> problem6 (abundant numbers)
TEST_CASE("Get abundant numbers up to specific limit", "[abundant_numbers]") {
    PairsVector expected{{12, 4},  {18, 3},  {20, 2},  {24, 12}, {30, 12},
                         {36, 19}, {40, 10}, {42, 12}, {48, 28}, {54, 12}};
    REQUIRE(abundantNumbers(55) == expected);
}