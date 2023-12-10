#include "catch2/catch_test_macros.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

std::string NumbersToString(
    const std::initializer_list<std::uint16_t>& values) {
    std::ostringstream oss;
    for (const auto& value : values)
        oss << std::hex << std::uppercase << std::setfill('0') << std::setw(2)
            << std::right << value;
    return oss.str();
}

TEST_CASE("convert numeric array/vector of numeric values to string",
          "[number_to_string]") {
    SECTION("Hexdecimal values to string") {
        REQUIRE(NumbersToString({0xBA, 0xAD, 0xF0, 0x0D}) == "BAADF00D");
        REQUIRE(NumbersToString({0xFF, 0xFF, 0xFF, 0xFF}) == "FFFFFFFF");
        REQUIRE(NumbersToString({0xAB, 0xCD, 0xEF}) == "ABCDEF");
        REQUIRE(NumbersToString({0xba, 0xad, 0xf0, 0x0d}) == "BAADF00D");
        REQUIRE(NumbersToString({0xab, 0xcD, 0xEf}) == "ABCDEF");
    }

    SECTION("Decimal values to string") {
        REQUIRE(NumbersToString({1, 2, 3, 4, 5, 6}) == "010203040506");
        REQUIRE(NumbersToString({0, 4, 2, 4, 5, 2, 1, 2}) ==
                "0004020405020102");
    }
}
