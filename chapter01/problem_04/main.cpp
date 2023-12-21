#include <catch2/catch_test_macros.hpp>
#include <iostream>

size_t largestPrimeSmallerThanGivenNumber(const size_t& limit) {
  constexpr auto is_prime = [](const auto& num) -> bool {
    if (num < 2) return false;
    for (size_t i = 2; i * i <= num; ++i) {
      if (num % i == 0) return false;
    }
    return true;
  };

  size_t prime = 0;
  for (size_t i = limit; i > 1; --i) {
    if (is_prime(i)) {
      prime = i;
      break;
    }
  }
  return prime;
}

// chapter-1 -> problem4 (largest prime smaller than given number)
TEST_CASE("Get largest prime smaller than given number", "[largest_prime_smaller_than_given_number]") {
  REQUIRE(largestPrimeSmallerThanGivenNumber(100) == 97);
  REQUIRE(largestPrimeSmallerThanGivenNumber(200) == 199);
  REQUIRE(largestPrimeSmallerThanGivenNumber(250) == 241);
  REQUIRE(largestPrimeSmallerThanGivenNumber(685) == 683);
}