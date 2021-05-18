#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// 1- create a list of numbers with 3 digits.
// 2- loop over this list and push_back to a new list the numbers
// which achieves the criteria.

bool is_armstrong(const std::size_t &number)
{
    const std::string num_str = std::to_string(number);
    if (num_str.size() != 3)
        return false;
    const auto first_digit = num_str.at(0) - '0';
    const auto second_digit = num_str.at(1) - '0';
    const auto third_digit = num_str.at(2) - '0';
    return number == (first_digit * first_digit * first_digit) +
                         (second_digit * second_digit * second_digit) +
                         (third_digit * third_digit * third_digit);
}

TEST_CASE("armstrong numbers are computed", "[armstrong]")
{
    REQUIRE(is_armstrong(153));
    REQUIRE(is_armstrong(370));
    REQUIRE(is_armstrong(371));
    REQUIRE(is_armstrong(407));

    REQUIRE_FALSE(is_armstrong(1634));
    REQUIRE_FALSE(is_armstrong(111));
    REQUIRE_FALSE(is_armstrong(120));
    REQUIRE_FALSE(is_armstrong(123));
    REQUIRE_FALSE(is_armstrong(140));
    REQUIRE_FALSE(is_armstrong(148));
}

int main(int argc, char *argv[])
{
    std::vector<std::size_t> numbers_with_3_digits(1000 - 100);
    std::vector<std::size_t> result;
    std::iota(numbers_with_3_digits.begin(), numbers_with_3_digits.end(), 100);
    std::copy_if(numbers_with_3_digits.begin(), numbers_with_3_digits.end(), std::back_inserter(result), is_armstrong);

    for (const auto &num : result)
        std::cout << num << '\n';
    
    // run tests
    int result_ = Catch::Session().run(argc, argv);
    // global clean-up...
    return result_;
}