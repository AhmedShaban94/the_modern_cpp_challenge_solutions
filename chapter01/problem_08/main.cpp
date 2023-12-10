#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

#include "catch2/catch_test_macros.hpp"

// 1- create a list of numbers with 3 digits.
// 2- loop over this list and push_back to a new list the numbers
// which achieves the criteria.

bool is_armstrong(const std::size_t& number) {
    size_t total = 0;
    const std::string num_str = std::to_string(number);
    for (const auto& ch : num_str)
        total += std::pow(ch - '0', num_str.size());
    return total == number;
}

TEST_CASE("armstrong numbers are computed", "[armstrong]") {
    REQUIRE(is_armstrong(153));
    REQUIRE(is_armstrong(370));
    REQUIRE(is_armstrong(371));
    REQUIRE(is_armstrong(407));
    REQUIRE(is_armstrong(1634));
    REQUIRE(is_armstrong(54748));
    REQUIRE(is_armstrong(548834));
    REQUIRE(is_armstrong(9926315));

    REQUIRE_FALSE(is_armstrong(111));
    REQUIRE_FALSE(is_armstrong(120));
    REQUIRE_FALSE(is_armstrong(123));
    REQUIRE_FALSE(is_armstrong(140));
    REQUIRE_FALSE(is_armstrong(148));
}