#include "catch2/catch.hpp"
#include <iostream>

std::size_t largestPrimeSmallerThanGivenNumber(const std::size_t& limit)
{
    constexpr auto is_prime = [](const auto& num) -> bool {
        for (size_t i = 2; i < num; ++i)
            if (num % i == 0)
                return false;
        return true;
    };

    std::size_t prime{ 0 };
    for (std::size_t i = limit; i > 1; --i)
        if (is_prime(i))
            return i;
}

// chapter-1 -> problem4 (largest prime smaller than given number)
TEST_CASE("Get largest prime smaller than given number", "[largest_prime]")
{
    REQUIRE(largestPrimeSmallerThanGivenNumber(100) == 97);
    REQUIRE(largestPrimeSmallerThanGivenNumber(200) == 199);
    REQUIRE(largestPrimeSmallerThanGivenNumber(250) == 241);
    REQUIRE(largestPrimeSmallerThanGivenNumber(685) == 683);
}