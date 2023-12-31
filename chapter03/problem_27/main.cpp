#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "catch2/catch_test_macros.hpp"

std::vector<std::string> split(const std::string& str, const std::string& delimiters) {
  auto is_delimiter = [delimiters](char ch) {
    return std::any_of(delimiters.begin(), delimiters.end(), [ch](char del) { return ch == del; });
  };

  std::string out;
  std::replace_copy_if(
      str.begin(), str.end(), std::back_inserter(out), [&](char ch) { return is_delimiter(ch); }, ' ');

  std::string token;
  std::istringstream iss{out};
  std::vector<std::string> tokens;
  while (iss >> token) tokens.push_back(token);

  return tokens;
}

TEST_CASE("Split string to vector of tokens given a set of specific delimiters", "[split_string]") {
  using namespace std::string_literals;
  REQUIRE(std::vector<std::string>{"This", "is", "a", "Sample"} == split("This is a Sample"s, " "));
  REQUIRE(std::vector<std::string>{"This", "is", "a", "Sample"} == split("This,is,a,Sample"s, ","));
  REQUIRE(std::vector<std::string>{"This", "is", "a", "Sample"} == split("This!is,a.Sample"s, "!,. "));
  REQUIRE(std::vector<std::string>{"This", "is", "a", "Sample"} == split("This,,is!a.Sample"s, ",!. "));
}