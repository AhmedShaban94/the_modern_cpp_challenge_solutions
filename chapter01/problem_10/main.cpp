#include <bitset>
#include <iostream>
#include <iterator>
#include <vector>

#include "catch2/catch_test_macros.hpp"

template <class container>
std::ostream& operator<<(std::ostream& os, const container& c) {
    std::copy(c.begin(), c.end(),
              std::ostream_iterator<typename container::value_type>(os, " "));
    return os;
}

std::vector<std::string> gray_code(size_t num) {
    std::vector<std::string> codes;
    for (size_t i = 0; i < (1 << num); ++i) {
        auto value = (i ^ (i >> 1));
        codes.emplace_back(std::bitset<32>(value).to_string().substr(32 - num));
    }
    return codes;
}

TEST_CASE("computation of gray code", "[gray_code]") {
    REQUIRE(gray_code(2) == std::vector<std::string>{"00", "01", "11", "10"});
    REQUIRE(gray_code(3) == std::vector<std::string>{"000", "001", "011", "010",
                                                     "110", "111", "101",
                                                     "100"});
    REQUIRE(gray_code(4) == std::vector<std::string>{
                                "0000", "0001", "0011", "0010", "0110", "0111",
                                "0101", "0100", "1100", "1101", "1111", "1110",
                                "1010", "1011", "1001", "1000"});
    REQUIRE(gray_code(5) ==
            std::vector<std::string>{
                "00000", "00001", "00011", "00010", "00110", "00111", "00101",
                "00100", "01100", "01101", "01111", "01110", "01010", "01011",
                "01001", "01000", "11000", "11001", "11011", "11010", "11110",
                "11111", "11101", "11100", "10100", "10101", "10111", "10110",
                "10010", "10011", "10001", "10000"});
}