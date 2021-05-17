#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    unsigned int limit;
    std::cout << "Enter the limit \n";
    std::cin >> limit;

    std::vector<size_t> divisors;
    std::vector<std::pair<int, int>> nums;
    for (int i = 1; i < limit; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            if (i % j == 0)
                divisors.push_back(j);
        }
        int divisors_sum
            = std::accumulate(divisors.begin(), divisors.end(), (size_t)0);
        if (divisors_sum > i)
            nums.emplace_back(i, divisors_sum - i);
    }

    std::cout << "pairs of abundant numbers and its abundance\n";
    for (const auto& pair : nums)
        std::cout << '(' << pair.first << ", " << pair.second << ")\n";

    return EXIT_SUCCESS;
}