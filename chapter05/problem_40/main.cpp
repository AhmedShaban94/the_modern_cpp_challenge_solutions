#include <iostream>
#include "catch2/catch_test_macros.hpp"
#include "date/date.h"

using namespace date::literals;
using date_t = date::year_month_day;

int daysBetweenTwoDates(const date_t& date_1, const date_t& date_2) {
    return std::abs((date::sys_days{date_1} - date::sys_days{date_2}).count());
}

TEST_CASE("Count days between two dates", "[days_between_two_dates]") {
    REQUIRE(daysBetweenTwoDates(2022_y / jan / 1, 2022_y / jan / 7) == 6);
    REQUIRE(daysBetweenTwoDates(2022_y / jan / 7, 2022_y / jan / 1) == 6);
    REQUIRE(daysBetweenTwoDates(2022_y / jan / 7, 2022_y / jan / 7) == 0);
    REQUIRE(daysBetweenTwoDates(2021_y / jan / 1, 2021_y / dec / 31) == 364);
    REQUIRE(daysBetweenTwoDates(2024_y / jan / 1, 2024_y / dec / 31) ==
            365);  // leap year
}