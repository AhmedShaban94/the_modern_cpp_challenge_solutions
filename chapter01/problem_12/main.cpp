#include <stdexcept>
#include <utility>
#include <vector>

#include "catch2/catch_test_macros.hpp"

std::pair<size_t, size_t> longestCollatzSequence(const size_t& limit) {
  if (limit < 2) {
    throw std::invalid_argument("Limit must be at least 2");
  }

  size_t maxLength = 0;
  size_t maxNumber = 0;
  std::vector<size_t> cache(limit + 1, 0);

  for (size_t currentNumber = 2; currentNumber <= limit; currentNumber++) {
    size_t currentLength = 0;
    size_t n = currentNumber;
    while (n != 1 && n >= currentNumber) {
      if ((n % 2) == 0)
        n = n / 2;
      else
        n = n * 3 + 1;
      currentLength++;
    }

    cache[currentNumber] = currentLength + cache[n];
    if (cache[currentNumber] > maxLength) {
      maxLength = cache[currentNumber];
      maxNumber = currentNumber;
    }
  }

  return std::make_pair(maxNumber, maxLength);
}

TEST_CASE("LongestCollatz Test") {
  SECTION("Limit1") {
    REQUIRE_THROWS_AS(longestCollatzSequence(1), std::invalid_argument);
  }

  SECTION("Limit2") {
    auto result = longestCollatzSequence(2);
    REQUIRE(result.first == 2);
    REQUIRE(result.second == 1);
  }

  SECTION("Limit10") {
    auto result = longestCollatzSequence(10);
    REQUIRE(result.first == 9);
    REQUIRE(result.second == 19);
  }

  SECTION("Limit100") {
    auto result = longestCollatzSequence(100);
    REQUIRE(result.first == 97);
    REQUIRE(result.second == 118);
  }

  SECTION("Limit1000") {
    auto result = longestCollatzSequence(1000);
    REQUIRE(result.first == 871);
    REQUIRE(result.second == 178);
  }

  SECTION("Limit10000") {
    auto result = longestCollatzSequence(10000);
    REQUIRE(result.first == 6171);
    REQUIRE(result.second == 261);
  }
}