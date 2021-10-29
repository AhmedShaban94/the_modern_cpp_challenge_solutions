#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

auto is_number = [](const std::string& s) {
        return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
    };

int main()
{
    const std::string str{ "AAA-AA 111" };
    std::pair<std::string, std::string> plate;
    std::string token;
    std::vector<std::string> tokens;
    std::istringstream iss{ str };
    while (std::getline(iss, token, ' '))
        tokens.push_back(token);
    if (tokens.size() == 2)
    {
        plate.first  = tokens.at(0);
        plate.second = tokens.at(1);
    }
    
    return EXIT_SUCCESS;
}