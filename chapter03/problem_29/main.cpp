#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> tokenize(const std::string& str, const char& delimiter)
{
    std::string token{};
    std::istringstream iss{ str };
    std::vector<std::string> tokens{};

    while (std::getline(iss, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

const auto is_upper_str = [](const std::string& str) {
    return !str.empty()
        and std::all_of(str.begin(), str.end(),
                        [](const char& ch) { return std::isupper(ch); });
};

const auto is_number = [](const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
};

bool validateNumber(const std::string& num)
{
    return is_number(num) and (num.size() == 4 or num.size() == 3);
}

bool validateString(const std::string& str)
{
    const auto splt_str = tokenize(str, '-');
    return !splt_str.empty() and splt_str.at(0).size() == 3
        and splt_str.at(1).size() == 2 and is_upper_str(splt_str.at(0))
        and is_upper_str(splt_str.at(1));
}

int main()
{
    // const std::string str{ "AAA-AA 111" };
    // std::pair<std::string, std::string> plate;
    // std::string token;
    // std::vector<std::string> tokens;
    // std::istringstream iss{ str };
    // while (std::getline(iss, token, ' '))
    //     tokens.push_back(token);
    // if (tokens.size() == 2)
    // {
    //     plate.first  = tokens.at(0);
    //     plate.second = tokens.at(1);
    // }
    const std::string str{ "AHMED" };

    return EXIT_SUCCESS;
}