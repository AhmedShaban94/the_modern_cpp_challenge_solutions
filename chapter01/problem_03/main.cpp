#include <iostream>

// chapter-1 -> problem 3 (least common multiple)
int main()
{
    unsigned int num1{ 0 }, num2{ 0 };
    std::cout << "Enter first number\n";
    std::cin >> num1;
    std::cout << "Enter second number\n";
    std::cin >> num2;

    int max = (num1 > num2) ? num1 : num2;
    do
    {
        if (max % num1 == 0 && max % num2 == 0)
        {
            std::cout << "LCM = \n" << max;
            break;
        }
        else
            ++max;
    } while (true);
    
    return EXIT_SUCCESS;
}