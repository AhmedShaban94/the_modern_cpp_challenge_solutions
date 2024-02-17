#include <exception>
#include <iostream>

#include "catch2/catch_test_macros.hpp"
#include "date/date.h"
#include "date/iso_week.h"

using namespace date::literals;
using date_t = date::year_month_day;

unsigned int daysBetweenTwoDates(const date_t& date_1, const date_t& date_2) {
  if (date_1.ok() and date_2.ok()) return std::abs((date::sys_days{date_1} - date::sys_days{date_2}).count());
  throw std::logic_error{"Date is invalid.\n"};
}

unsigned int dayNumberOfTheYear(const date_t& date) {
  const auto year = date.year();
  const auto startOfTheYear = date::year_month_day{year / jan / 1};
  try {
    return (daysBetweenTwoDates(date, startOfTheYear) + 1);
  } catch (const std::exception&) {
    throw;
  }
}

auto weekNumberOfTheYear(const date_t& date) {
  if (date.ok()) return static_cast<unsigned int>(iso_week::year_weeknum_weekday{date}.weeknum());
  throw std::logic_error{"Date is invalid.\n"};
}

TEST_CASE("Given a date, get day number of the year", "[day_number_of_the_year]") {
  using namespace date::literals;
  REQUIRE(dayNumberOfTheYear(2022_y / jan / 9) == 9);
  REQUIRE(dayNumberOfTheYear(2022_y / jan / 1) == 1);
  REQUIRE(dayNumberOfTheYear(2021_y / dec / 1) == 335);

  REQUIRE_THROWS_AS(dayNumberOfTheYear(2021_y / 13 / 1), std::logic_error);
  REQUIRE_THROWS_AS(dayNumberOfTheYear(2021_y / jan / 35), std::logic_error);
}

TEST_CASE("Given a date, get week number of the year", "[week_number_of_the_year]") {
  using namespace date::literals;
  REQUIRE(weekNumberOfTheYear(2022_y / jan / 9) == 1);
  REQUIRE(weekNumberOfTheYear(2022_y / feb / 1) == 5);
  REQUIRE(weekNumberOfTheYear(2021_y / dec / 1) == 48);
  REQUIRE(weekNumberOfTheYear(2016_y / 1 / 3) == 53);

  REQUIRE_THROWS_AS(weekNumberOfTheYear(2021_y / 13 / 1), std::logic_error);
  REQUIRE_THROWS_AS(weekNumberOfTheYear(2021_y / jan / 35), std::logic_error);
}