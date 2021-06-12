#include <iostream>

// chapter-1 -> problem4 (largest prime smaller than given number)
int main()
{
    unsigned int limit{ 0 }, prime{ 0 };
    std::cout << "Enter the number\n";
    std::cin >> limit;

    for (std::size_t i = 2; i < limit; ++i)
    {
        for (std::size_t j = 0; j <= i; ++j)
            if (j % i == 0)
                prime = i;
    }
    std::cout << "largest prime number before the given limit " << limit
              << " is :" << prime << '\n';
    return EXIT_SUCCESS;
}