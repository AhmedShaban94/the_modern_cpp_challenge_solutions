#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "catch2/catch_test_macros.hpp"

bool validatePlateNumber(const std::string& plateNumber) {
  // plate-format {DDD-DD NNN} or {DDD-DD NNNN}
  const std::regex reg{R"([A-Z]{3}-[A-Z]{2} \d{3,4})"};
  return std::regex_search(plateNumber, reg);
}

std::vector<std::string> extractPlateNumbers(const std::string& txt) {
  const std::regex reg{R"(([A-Z]{3}-[A-Z]{2} \d{3,4})+)"};
  std::sregex_iterator itr{txt.begin(), txt.end(), reg};
  std::sregex_iterator end{};
  std::vector<std::string> results;

  while (itr != end) {
    if ((*itr)[1].matched) results.push_back(itr->str());
    itr++;
  }

  return results;
}

TEST_CASE("validate plate number format", "[validate_plate_number]") {
  REQUIRE(validatePlateNumber("DDD-DD 123"));
  REQUIRE(validatePlateNumber("DDD-DD 1234"));
  REQUIRE(validatePlateNumber("ABC-DE 123"));
  REQUIRE(validatePlateNumber("ABC-DE 1234"));

  REQUIRE_FALSE(validatePlateNumber(""));
  REQUIRE_FALSE(validatePlateNumber("DDD-DDD 123"));
  REQUIRE_FALSE(validatePlateNumber("DDD-dd 12"));
  REQUIRE_FALSE(validatePlateNumber("ddd-DD 1"));
  REQUIRE_FALSE(validatePlateNumber("DDDD-DD 1"));
  REQUIRE_FALSE(validatePlateNumber("DDD-DD"));
  REQUIRE_FALSE(validatePlateNumber("123-45 ABCD"));
}

TEST_CASE("extract plate number from a given text", "[extract_plate_number]") {
  const std::string text{"AAA-AA 123qwe-ty 1234 ABC-DE 123456..XYZ-WW 0001"};
  const std::vector<std::string> expected{"AAA-AA 123", "ABC-DE 1234", "XYZ-WW 0001"};
  REQUIRE(expected == extractPlateNumbers(text));
}