#include <iostream>

void printPascal(const size_t& rows_count = 5) {
    for (size_t row = 0; row < rows_count + 1; row++) {
        size_t val{1};
        for (size_t i = 1; i < (rows_count - row + 1); i++)
            std::cout << " ";

        for (size_t i = 1; i <= row; i++) {
            std::cout << val << " ";
            val = val * (row - i) / i;
        }

        std::cout << "\n";
    }
}

int main() {
    printPascal();
    return EXIT_SUCCESS;
}