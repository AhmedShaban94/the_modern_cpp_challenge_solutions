#include "date/date.h"
#include "date/tz.h"
#include "date/tz_private.h"
#include <iomanip>
#include <iostream>
#include <vector>

struct user
{
    std::string m_name{};
    const date::time_zone *m_zone;
    explicit user(std::string name, std::string zone) : m_name{std::move(name)}, m_zone{date::locate_zone(std::move(zone))} {}
};

template <class Duration, class TimeZonePtr>
void printMeetingsTimes(
    const date::zoned_time<Duration, TimeZonePtr> &time,
    const std::vector<user> &users)
{
    std::cout
        << std::left << std::setw(15) << std::setfill(' ')
        << "Local time: "
        << time << '\n';
    for (auto const &user : users)
    {
        std::cout
            << std::left << std::setw(15) << std::setfill(' ')
            << user.m_name
            << date::zoned_time<Duration, TimeZonePtr>(user.m_zone, time)
            << '\n';
    }
}

int main()
{
    std::vector<user> users{
        user{"Budapest", "Europe/Budapest"},
        user{"Berlin", "Europe/Berlin"},
        user{"New_York", "America/New_York"}};
    unsigned int h, m;
    std::cout << "Hour:";
    std::cin >> h;
    std::cout << "Minutes:";
    std::cin >> m;
    date::year_month_day today =
        date::floor<date::days>(std::chrono::system_clock::now());
    auto localtime = date::zoned_time<std::chrono::minutes>(
        date::current_zone(),
        static_cast<date::local_days>(today) + std::chrono::hours{h} + std::chrono::minutes{m});
    printMeetingsTimes(localtime, users);
    return EXIT_SUCCESS;
}