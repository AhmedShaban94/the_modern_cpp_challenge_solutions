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

std::optional<urlParts> parse_url(const std::string &url)
{
    const std::regex regexp{R"(^(\w+):\/\/([\w.-]+)(:(\d+))?([\w\/\.]+)?(\?([\w=&]*)(#?(\w+))?)?$)"};
    std::smatch matches;
    std::regex_search(url, matches, regexp);
    for (const auto &m : matches)
        std::cout << m.str() << '\n';
    return std::nullopt;
}

int main()
{
    const std::string link{"https://bbc.com:80/en/index.html?lite=true#ui"};
    parse_url(link);
    return EXIT_SUCCESS;
}