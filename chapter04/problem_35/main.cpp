#include "filesystem.h"
#include <cmath>
#include <iostream>
#include <string>

namespace fs = std::filesystem;
struct HumanReadable
{
    std::uintmax_t size{};
    friend std::ostream& operator<<(std::ostream& os, HumanReadable hr)
    {
        std::size_t i{};
        double mantissa = hr.size;
        while (mantissa >= 1024.)
        {
            mantissa /= 1024.;
            ++i;
        }
        mantissa = std::ceil(mantissa * 10.) / 10.;
        os << mantissa << "BKMGTPE"[i];
        return i == 0 ? os : os << "B (" << hr.size << ')';
    }
};

auto directorySize(const std::string& pathString, bool followSymbolicLink)
{
    const auto path = fs::path{ pathString };
    if (!fs::exists(path))
    {
        std::cerr << "Directory doesn't exists.";
        std::exit(EXIT_FAILURE);
    }

    const auto directoryOption
        = (followSymbolicLink ? fs::directory_options::follow_directory_symlink
                              : fs::directory_options::none);
    std::uintmax_t size{ 0 };
    for (const auto& entry :
         fs::recursive_directory_iterator(path, directoryOption))
        size += (fs::is_regular_file(entry) ? fs::file_size(entry) : 0);

    return size;
}

int main()
{
    std::cout << "Enter path to specified directory\n";
    std::string pathString{};
    std::getline(std::cin, pathString);
    const auto dirSize = HumanReadable{ directorySize(pathString, false) };
    std::cout << "Directory size: " << dirSize << '\n';
    return EXIT_SUCCESS;
}