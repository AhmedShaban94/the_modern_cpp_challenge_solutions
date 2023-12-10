#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "catch2/catch_test_macros.hpp"

template <class container>
std::ostream& operator<<(std::ostream& os, const container& c) {
    std::copy(c.begin(), c.end(),
              std::ostream_iterator<typename container::value_type>(os, " "));
    return os;
}

std::vector<std::size_t> prime_factors(std::size_t number) {
    std::vector<std::size_t> prime_factors{};
    while (number % 2 == 0) {
        prime_factors.push_back(2);
        number /= 2;
    }

    for (std::size_t i = 3; i <= std::sqrt(number); i += 2) {
        while (number % i == 0) {
            prime_factors.push_back(i);
            number /= i;
        }
    }

    if (number > 2)
        prime_factors.push_back(number);
    return prime_factors;
}

TEST_CASE("computation of prime factors", "[prime_factors]") {
    REQUIRE(prime_factors(42) == std::vector<std::size_t>{2, 3, 7});
    REQUIRE(prime_factors(8) == std::vector<std::size_t>{2, 2, 2});
    REQUIRE(prime_factors(600) == std::vector<std::size_t>{2, 2, 2, 3, 5, 5});
    REQUIRE(prime_factors(851) == std::vector<std::size_t>{23, 37});
    REQUIRE(prime_factors(475) == std::vector<std::size_t>{5, 5, 19});
    REQUIRE(prime_factors(143) == std::vector<std::size_t>{11, 13});
}