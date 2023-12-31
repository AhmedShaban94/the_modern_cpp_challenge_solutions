#include <iostream>
#include <list>
#include <vector>

#include "catch2/catch_test_macros.hpp"

template <typename Container, typename... Args>
void add_range(Container& cont, Args&&... args) {
  (cont.push_back(args), ...);
}

TEST_CASE("testing adding range to container", "[add_range]") {
  std::vector vec{1, 2, 3};
  add_range(vec, 4, 5, 6);
  REQUIRE(vec == std::vector{1, 2, 3, 4, 5, 6});

  std::list ls{1, 2, 3};
  add_range(ls, 4, 5, 6);
  REQUIRE(ls == std::list{1, 2, 3, 4, 5, 6});
}