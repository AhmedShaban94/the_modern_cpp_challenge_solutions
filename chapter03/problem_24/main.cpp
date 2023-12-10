#include "catch2/catch_test_macros.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::uint16_t> StringToNumberSequence(const std::string& str) {
    std::string temp_str{str};
    std::vector<std::uint16_t> output;
    std::transform(str.begin(), str.end(), std::back_inserter(temp_str),
                   ::toupper);
    for (std::string::size_type i{0}; i < str.size(); i += 2) {
        const auto substr = temp_str.substr(i, 2);
        const auto num = std::strtoul(substr.c_str(), nullptr, 16);
        output.push_back(num);
    }
    return output;
}

TEST_CASE("convert string to array/vector of numeric values",
          "[string_to_number_seq]") {
    SECTION("Hexdecimal values to string") {
        REQUIRE(StringToNumberSequence("BAADF00D") ==
                std::vector<std::uint16_t>{0XBA, 0xAD, 0xF0, 0X0D});
        REQUIRE(StringToNumberSequence("FFFFFFFF") ==
                std::vector<std::uint16_t>{0xFF, 0xFF, 0xFF, 0xFF});
        REQUIRE(StringToNumberSequence("ABCDEF") ==
                std::vector<std::uint16_t>{0XAB, 0xCD, 0xEF});
        REQUIRE(StringToNumberSequence("BAADF00D") ==
                std::vector<std::uint16_t>{0xba, 0xad, 0xf0, 0x0d});
        REQUIRE(StringToNumberSequence("ABCDEF") ==
                std::vector<std::uint16_t>{0xab, 0xcD, 0xEf});
    }

    SECTION("String to decimal values") {
        REQUIRE(StringToNumberSequence("010203040506") ==
                std::vector<std::uint16_t>{1, 2, 3, 4, 5, 6});
        REQUIRE(StringToNumberSequence("0004020405020102") ==
                std::vector<std::uint16_t>{0, 4, 2, 4, 5, 2, 1, 2});
    }
}