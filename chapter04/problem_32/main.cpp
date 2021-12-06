#include <iostream>

void printPascal(const std::size_t& rows_count = 5)
{
    for (std::size_t row = 0; row < rows_count + 1; row++)
    {
        std::size_t val{1};
        for (std::size_t i = 1; i < (rows_count - row + 1); i++)
            std::cout << " ";

        for (std::size_t i = 1; i <= row; i++)
        {
            std::cout << val << " ";
            val = val * (row - i) / i;
        }

        std::cout << "\n";
    }
}

int main()
{    
    printPascal();
    return EXIT_SUCCESS;
}