#include <exception>
#include <iostream>

#include "catch2/catch_test_macros.hpp"
#include "date/date.h"
#include "date/iso_week.h"

using date_t = date::year_month_day;
unsigned int getWeekDay(const date_t& date) {
  if (date.ok()) return date::weekday{date}.iso_encoding();
  throw std::logic_error{"Date in invalid.\n"};
}

TEST_CASE("Given a date, get the iso weekday of this date", "[get_iso_weekday]") {
  using namespace date::literals;
  REQUIRE(getWeekDay(2022_y / jan / 9) == 7);
  REQUIRE(getWeekDay(2022_y / jan / 1) == 6);
  REQUIRE(getWeekDay(2021_y / dec / 1) == 3);

  REQUIRE_THROWS_AS(getWeekDay(2021_y / 13 / 1), std::logic_error);
  REQUIRE_THROWS_AS(getWeekDay(2021_y / jan / 35), std::logic_error);
}