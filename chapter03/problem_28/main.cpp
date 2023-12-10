#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "catch2/catch_test_macros.hpp"

std::string longestPalindrome(const std::string& str) {
    auto is_palindrome = [](const std::string& str) {
        if (str.empty())
            return false;
        auto r_str{str};
        std::reverse(r_str.begin(), r_str.end());
        return str == r_str;
    };

    std::vector<std::string> palindromes;
    for (std::size_t i{0}; i < str.size(); ++i) {
        for (std::size_t j{i + 1}; j < str.size(); ++j) {
            std::string substr = str.substr(i, j - i + 1);
            if (is_palindrome(substr))
                palindromes.push_back(substr);
        }
    }

    return *std::max_element(
        palindromes.begin(), palindromes.end(),
        [](const std::string& str1, const std::string& str2) {
            return str1.size() < str2.size();
        });
}

TEST_CASE("get longest palindromic substring from a given string",
          "[longest_palindrome]") {
    using namespace std::string_literals;
    REQUIRE(longestPalindrome("sahararahnide") == "hararah"s);
    REQUIRE(longestPalindrome("aaabb") == "aaa"s);
    REQUIRE(longestPalindrome("abbba") == "abbba"s);
    REQUIRE(longestPalindrome("racecar") == "racecar"s);
    REQUIRE(longestPalindrome("baaaabad") == "baaaab"s);
}