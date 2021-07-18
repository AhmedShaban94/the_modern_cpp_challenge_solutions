#define CATCH_CONFIG_MAIN
#include "Ipv4.hpp"
#include "catch2/catch.hpp"

template <typename T>
void print(const T &vec)
{
    for (const auto &element : vec)
        std::cout << element << '\n';
}

std::vector<IPv4> enumrate_IPs_in_range(const IPv4 &first, const IPv4 &last)
{
    const auto first_decimal = static_cast<std::uint32_t>(first);
    const auto last_decimal = static_cast<std::uint32_t>(last);
    std::vector<IPv4> range;

    if (first_decimal < last_decimal)
        for (std::size_t i = first_decimal; i <= last_decimal; ++i)
            range.emplace_back(i);
    else
        throw std::runtime_error{"invalid range"};
    return range;
}

TEST_CASE("enumrate IPv4 Addresses in range", "[IPv4]")
{
    SECTION("valid range")
    {
        std::vector<IPv4> expectedRange(256);
        std::iota(expectedRange.begin(), expectedRange.end(), IPv4{"255.255.255.0"});
        REQUIRE(expectedRange == enumrate_IPs_in_range(IPv4{"255.255.255.0"}, IPv4{"255.255.255.255"}));
    }
}