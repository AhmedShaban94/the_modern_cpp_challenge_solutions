#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>
#include "catch2/catch_test_macros.hpp"

template <typename T>
std::string join_sequence(const std::vector<T>& vec,
                          const std::string_view deli) {
    if (vec.empty())
        return std::string{};

    std::ostringstream oss;
    oss << std::setprecision(1) << std::fixed;

    std::copy(vec.begin(), std::prev(vec.end()),
              std::ostream_iterator<T>(oss, deli.data()));
    oss << *std::prev(vec.end());
    return oss.str();
}

TEST_CASE("Join vector/sequence into single string using a specific delimiter",
          "[capitaliz_article]") {
    using namespace std::string_literals;
    REQUIRE(join_sequence(std::vector<int>{}, ", ") == ""s);
    REQUIRE(join_sequence(std::vector{1, 2, 3, 4, 5}, ", ") ==
            "1, 2, 3, 4, 5"s);
    REQUIRE(join_sequence(std::vector{1.0, 2.0, 3.0, 4.0, 5.0}, ", ") ==
            "1.0, 2.0, 3.0, 4.0, 5.0"s);
    REQUIRE(join_sequence(std::vector{1, 2, 3, 4, 5}, "\n") ==
            "1\n2\n3\n4\n5"s);
    REQUIRE(join_sequence(std::vector{"This", "is", "a", "test"}, " ") ==
            "This is a test"s);
    REQUIRE_FALSE(join_sequence(std::vector{1, 2, 3, 4, 5}, ", ") ==
                  "1, 2, 3, 4 , 5"s);
}