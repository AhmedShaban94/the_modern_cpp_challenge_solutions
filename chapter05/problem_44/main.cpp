#include "date/date.h"
#include <exception>
#include <iomanip>
#include <iostream>

using date_t = date::year_month_day;
auto weekDay(const date_t &date)
{
    if (date.ok())
        return date::weekday{date}.iso_encoding();
    throw std::logic_error{"Date is invalid.\n"};
}

void printMonthCalender(const date_t &date)
{
    if (!date.ok())
        throw std::logic_error{"Date is invalid.\n"};
    std::cout << "Mon Tue Wed Thu Fri Sat Sun" << '\n';
    const auto calenderFirstDay = weekDay(date);
    const auto calenderLastDay = static_cast<unsigned int>
        (date::year_month_day_last{date.year(), date::month_day_last{date.month()}}.day());

    std::size_t index = 1;
    for (std::size_t day{1}; day < calenderFirstDay; ++day, ++index)
    {
        std::cout << " ";
    }
    for (std::size_t day{1}; day <= calenderLastDay; ++day)
    {
        std::cout << std::right << std::setfill(' ') << std::setw(3)
                  << day << ' ';
        if (index++ % 7 == 0)
            std::cout << '\n';
    }
    std::cout << '\n';
}

int main()
{
    using namespace date::literals;
    printMonthCalender(2022_y / dec / 13);
    return EXIT_SUCCESS;
}