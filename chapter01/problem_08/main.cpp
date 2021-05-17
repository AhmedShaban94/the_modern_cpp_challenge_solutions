#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// 1- create a list of numbers with 3 digits.
// 2- loop over this list and push_back to a new list the numbers
// which achieves the criteria.

bool is_armstrong(const std::size_t &number)
{
    const std::string num_str = std::to_string(number);
    const auto first_digit = num_str.at(0) - '0';
    const auto second_digit = num_str.at(1) - '0';
    const auto third_digit = num_str.at(2) - '0';
    return number == (first_digit * first_digit * first_digit) +
                         (second_digit * second_digit * second_digit) +
                         (third_digit * third_digit * third_digit);
}

int main()
{
    std::vector<std::size_t> numbers_with_3_digits(1000 - 100);
    std::vector<std::size_t> result;
    std::iota(numbers_with_3_digits.begin(), numbers_with_3_digits.end(), 100);
    std::copy_if(numbers_with_3_digits.begin(), numbers_with_3_digits.end(), std::back_inserter(result), is_armstrong);

    for (const auto &num : result)
        std::cout << num << '\n';
    return EXIT_SUCCESS;
}