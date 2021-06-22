#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"
#include <bitset>
#include <iostream>
#include <iterator>
#include <vector>

std::string numeric_to_roman(std::size_t num)
{
    using RomanPair = std::pair<std::size_t, std::string>;
    std::vector<RomanPair> roman{
                                {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"},
                                {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    std::string roman_str; 
    for(const auto& [key, value] : roman)
    {
        while(num >= key)
        {
            roman_str += value; 
            num -= key; 
        }
    }

    return roman_str; 
}

TEST_CASE("numeric to roman conversion", "[numeric_to_roman]")
{
    REQUIRE(numeric_to_roman(3999) == "MMMCMXCIX");
    REQUIRE(numeric_to_roman(2245) == "MMCCXLV"); 
    REQUIRE(numeric_to_roman(1908) == "MCMVIII"); 
    REQUIRE(numeric_to_roman(2700) == "MMDCC"); 
    REQUIRE(numeric_to_roman(687) == "DCLXXXVII"); 
}

int main(int argc, char* argv[])
{
    // run tests
    int result_ = Catch::Session().run(argc, argv);
    // global clean-up...
    return result_;
}