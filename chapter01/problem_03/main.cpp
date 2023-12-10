#include <iostream>
#include <numeric>

#include "catch2/catch_test_macros.hpp"

size_t leastCommonMultiple(const size_t& num1,
                                const size_t& num2) {
    auto max = (num1 > num2) ? num1 : num2;
    do {
        if (max % num1 == 0 && max % num2 == 0)
            return max;
        ++max;
    } while (true);
}

// chapter-1 -> problem 3 (least common multiple)
TEST_CASE("Get least common multiple", "[least_common_multiple]") {
    REQUIRE(leastCommonMultiple(10, 5) == std::lcm(10, 5));
    REQUIRE(leastCommonMultiple(15, 3) == std::lcm(15, 3));
    REQUIRE(leastCommonMultiple(22, 2) == std::lcm(22, 2));
    REQUIRE(leastCommonMultiple(35, 5) == std::lcm(35, 5));
    REQUIRE(leastCommonMultiple(50, 5) == std::lcm(50, 5));
    REQUIRE(leastCommonMultiple(100, 20) == std::lcm(100, 20));
}