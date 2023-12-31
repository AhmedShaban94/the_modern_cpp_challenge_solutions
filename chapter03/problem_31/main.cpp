#include <algorithm>
#include <iostream>
#include <regex>

#include "catch2/catch_test_macros.hpp"

std::string transform_date(const std::string& date) {
  const std::regex regexp{R"((\d{1,2})(\.|-|/)(\d{1,2})(\.|-|/)(\d{1,4}))"};
  return std::regex_replace(date.c_str(), regexp, std::string(R"($5-$3-$1)"));
}

TEST_CASE("transform date from dd-mm-yyyy of dd.mm.yyyy to yyyy-mm-dd", "[transform_date]") {
  using namespace std::string_literals;
  REQUIRE(""s == transform_date(""));
  REQUIRE("2011-11-11"s == transform_date("11-11-2011"));
  REQUIRE("2012-12-12"s == transform_date("12.12.2012"));
  REQUIRE("this text from 2011-11-11"s == transform_date("this text from 11-11-2011"));
  REQUIRE_FALSE("11-11-2021"s == transform_date("11.11.2021"));
}