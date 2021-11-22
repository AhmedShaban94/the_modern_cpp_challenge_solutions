#include "catch2/catch.hpp"
#include <iostream>
#include <optional>
#include <regex>
#include <string>
#include <vector>

struct urlParts
{
    std::string protocol;
    std::string domain;
    std::optional<std::size_t> port;
    std::optional<std::string> path;
    std::optional<std::string> query;
    std::optional<std::string> fragment;
};

std::ostream &operator<<(std::ostream &os, const urlParts &parts)
{
    os << "Protocol: " << parts.protocol << '\n';
    os << "Domain: " << parts.domain << '\n';
    if (parts.port.has_value())
        os << "Port: " << parts.port.value() << '\n';
    if (parts.path.has_value())
        os << "Path: " << parts.path.value() << '\n';
    if (parts.query.has_value())
        os << "Query: " << parts.query.value() << '\n';
    if (parts.fragment.has_value())
        os << "Fragment: " << parts.fragment.value() << '\n';

    return os;
}

std::optional<urlParts> parse_url(const std::string &url)
{
    const std::regex regexp{R"(^(\w+):\/\/([\w.-]+)(:(\d+))?([\w\/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$)"};
    std::smatch matches;
    const auto found = std::regex_search(url, matches, regexp);
    if (found)
    {
        if (matches[1].matched and matches[2].matched)
        {
            urlParts parts;
            parts.protocol = matches[1].str();
            parts.domain = matches[2].str();

            if (matches[4].matched)
                parts.port.emplace(std::stoull(matches[4]));
            if (matches[5].matched)
                parts.path.emplace(matches[5].str());
            if (matches[7].matched)
                parts.query.emplace(matches[7].str());
            if (matches[9].matched)
                parts.fragment.emplace(matches[9].str());

            return parts;
        }
    }
    return std::nullopt;
}

TEST_CASE("parse URL given uri text", "[parse_url]")
{
    using namespace std::string_literals;
    const auto url = "https://packt.com"s;
    const auto parts = parse_url(url);
    REQUIRE(parts.has_value());
    REQUIRE(parts.value().protocol == "https"s);
    REQUIRE(parts.value().domain == "packt.com"s);

    REQUIRE_FALSE(parts.value().port.has_value());
    REQUIRE_FALSE(parts.value().path.has_value());
    REQUIRE_FALSE(parts.value().query.has_value());
    REQUIRE_FALSE(parts.value().fragment.has_value());
}