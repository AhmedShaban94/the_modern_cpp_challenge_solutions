#include "catch2/catch.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::string CapitalizArticle(const std::string& str)
{
    std::string out;
    std::string token;
    std::istringstream iss{ str };
    while (iss >> token)
    {
        token[0] = std::toupper(token[0]);
        out.append(token + " ");
    }
    out.erase(std::prev(out.end()));
    return out;
}

TEST_CASE("Capitalize every first character of the word", "[capitaliz_article]")
{
    REQUIRE(CapitalizArticle("the modern c++ challenger") == "The Modern C++ Challenger"); 
    REQUIRE(CapitalizArticle("this is c++") == "This Is ")
}