#include <fstream>
#include <iostream>
#include <sstream>

void deleteEmptyLines(const std::string &filePath)
{
    std::ifstream ifs{filePath};
    if (ifs)
    {
        std::string line;
        std::stringstream ss;
        while (std::getline(ifs, line, '\n'))
            if (!line.empty())
                ss << (line + "\n");
        std::ofstream ofs{filePath};
        ofs << ss.str();
    }
    else
        throw std::runtime_error{"couldn't open file."};
}
int main()
{
    const std::string filePath{"test.txt"};
    try
    {
        deleteEmptyLines(filePath);
    }
    catch (std::exception &ex)
    {
        std::cerr << "ERROR: " << ex.what() << '\n';
        std::exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}