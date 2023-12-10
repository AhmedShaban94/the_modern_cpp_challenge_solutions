#include <algorithm>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>
#include "catch2/catch_test_macros.hpp"

template <typename Container, typename... Args>
bool contains_any(const Container& cont, Args... args) {
    using T = std::common_type_t<Args...>;
    std::vector<T> params{args...};
    return std::any_of(params.begin(), params.end(), [&cont](const auto& ele) {
        return std::find(cont.begin(), cont.end(), ele) != cont.end();
    });
}

template <typename Container, typename... Args>
bool contains_all(const Container& cont, Args... args) {
    using T = std::common_type_t<Args...>;
    std::vector<T> params{args...};
    return std::all_of(params.begin(), params.end(), [&cont](const auto& ele) {
        return std::find(cont.begin(), cont.end(), ele) != cont.end();
    });
}

template <typename Container, typename... Args>
bool contains_none(const Container& cont, Args... args) {
    using T = std::common_type_t<Args...>;
    std::vector<T> params{args...};
    return std::none_of(params.begin(), params.end(), [&cont](const auto& ele) {
        return std::find(cont.begin(), cont.end(), ele) != cont.end();
    });
}

TEST_CASE("Testing (contains) functions", "[contains]") {
    std::vector<size_t> vec{1, 2, 3, 4, 5, 6, 7, 8};

    SECTION("Testing (contains_any)") {

        REQUIRE(contains_any(vec, 1));
        REQUIRE(contains_any(vec, 1, 2));
        REQUIRE(contains_any(vec, 4, 5, 6));

        REQUIRE_FALSE(contains_any(vec, 10));
        REQUIRE_FALSE(contains_any(vec, -5));
    }

    SECTION("Testing (contains_all)") {
        REQUIRE(contains_all(vec, 1));
        REQUIRE(contains_all(vec, 1, 2));
        REQUIRE(contains_all(vec, 4, 5, 6));

        REQUIRE_FALSE(contains_all(vec, 4, 5, 11));
        REQUIRE_FALSE(contains_all(vec, 10));
        REQUIRE_FALSE(contains_all(vec, -5));
    }

    SECTION("Testing (contains_none)") {
        REQUIRE(contains_none(vec, 11));
        REQUIRE(contains_none(vec, 11, 22));
        REQUIRE(contains_none(vec, 44, 55, 66));

        REQUIRE_FALSE(contains_none(vec, 4, 5, 11));
        REQUIRE_FALSE(contains_none(vec, 1, 2));
        REQUIRE_FALSE(contains_none(vec, 5));
    }
}