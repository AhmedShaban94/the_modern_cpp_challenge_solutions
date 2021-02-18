#include <iostream>

// chapter-1 -> problem 2 (greatest common multiple)
int main()
{
    unsigned int num1{ 0 }, num2{ 0 };
    std::cout << "Enter first number \n";
    std::cin >> num1;
    std::cout << "Enter second number \n";
    std::cin >> num2;

    while (num2 != 0)
    {
        unsigned int t = num1 % num2;
        num1           = num2;
        num2           = t;
    }
    std::cout << "GCD: " << num1 << '\n';
    return EXIT_SUCCESS;
}
