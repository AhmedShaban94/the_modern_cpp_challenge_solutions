#include <bitset>
#include <iostream>
#include <iterator>
#include <vector>
#include "catch2/catch.hpp"

bool validate_ISBN(const std::string_view str) {
    std::size_t total{0};
    for (std::size_t i = 10; i >= 2; --i) {
        const auto num = str.at(10 - i) - '0';
        total += num * i;
    }
    str.back() == 'X' ? total += 10 : total += str.back() - '0';
    return total % 11 == 0;
}

TEST_CASE("ISBN-10 code validation", "[validate_ISBN]") {
    REQUIRE(validate_ISBN("0136091814") == true);
    REQUIRE(validate_ISBN("0136091812") == false);
    REQUIRE(validate_ISBN("007462542X") == true);
    REQUIRE(validate_ISBN("0112112425") == false);
}