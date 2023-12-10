#include <iostream>
#include <numeric>

#include <catch2/catch_test_macros.hpp>

size_t greatestCommonDivisor(size_t num1, size_t num2) {

    while (num2 != 0) {
        auto t = num1 % num2;
        num1 = num2;
        num2 = t;
    }

    return num1;
}

// chapter 1 -> problem 2 (greatest common divisor)
TEST_CASE("Get greatest common divisor", "[greatest_common_divisor]") {
    REQUIRE(greatestCommonDivisor(10, 5) == std::gcd(10, 5));
    REQUIRE(greatestCommonDivisor(15, 3) == std::gcd(15, 3));
    REQUIRE(greatestCommonDivisor(22, 2) == std::gcd(22, 2));
    REQUIRE(greatestCommonDivisor(35, 5) == std::gcd(35, 5));
    REQUIRE(greatestCommonDivisor(50, 5) == std::gcd(50, 5));
    REQUIRE(greatestCommonDivisor(100, 20) == std::gcd(100, 20));
}