#include <bitset>
#include <iostream>
#include <iterator>
#include <vector>

std::pair<size_t, size_t> longest_collatz(const size_t& limit) {
  size_t length{0};
  size_t number{0};
  std::vector<size_t> cache(limit + 1, 0);

  for (size_t i = 2; i <= limit; i++) {
    auto n = i;
    size_t steps{0};
    while (n != 1 && n >= i) {
      if ((n % 2) == 0)
        n = n / 2;
      else
        n = n * 3 + 1;
      steps++;
    }

    cache[i] = steps + cache[n];
    if (cache[i] > length) {
      length = cache[i];
      number = i;
    }
  }

  return std::make_pair(number, length);
}

int main() {
  auto [number, length] = longest_collatz(1000000);
  std::cout << number << ", " << length << '\n';
  return EXIT_SUCCESS;
}