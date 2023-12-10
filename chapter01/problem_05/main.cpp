#include <algorithm>
#include <iostream>
#include <vector>
#include "catch2/catch.hpp"

using PairsVector = std::vector<std::pair<std::size_t, std::size_t>>;

PairsVector sexyPrimePairs(const std::size_t& limit) {
    auto is_prime = [](const auto& num) {
        for (size_t i = 2; i < num; ++i)
            if (num % i == 0)
                return false;
        return true;
    };

    PairsVector sexyPrimes{};
    for (std::size_t i = 2; i <= limit - 6; ++i)
        if (is_prime(i) && is_prime(i + 6))
            sexyPrimes.emplace_back(i, i + 6);
    return sexyPrimes;
}

// chapter-1 -> problem5 (sexy prime pairs)
TEST_CASE("Get sexy prime pairs with given number", "[sexy_prime_pairs]") {
    PairsVector expectedVec{{5, 11},  {7, 13},  {11, 17}, {13, 19},
                            {17, 23}, {23, 29}, {31, 37}, {37, 43},
                            {41, 47}, {47, 53}, {53, 59}};
    REQUIRE(sexyPrimePairs(59) == expectedVec);
}