#include <iostream> 
#include <vector> 
#include <algorithm>

//chapter-1 -> problem5 (sexy prime numbers)
int main()
{
	unsigned int limit{};
	std::vector<int> prime_nums, sexy_primes;
	std::cout << "Enter the limit number\n";
	std::cin >> limit;
    auto is_prime = [](const auto& num)-> bool
    { 
        for (size_t i = 2; i < num; ++i)
			if (num % i == 0)
				return false;
		return true;
     }; 

	for (std::size_t i = 2; i <= limit; ++i)
		if (is_prime(i))
			prime_nums.push_back(i);

	for (std::size_t i = 2; i < prime_nums.size(); ++i)
	{
		for (std::size_t j = 2; j < i; ++j)
		{
			if ((prime_nums.at(i) - prime_nums.at(j)) == 6)
			{
				sexy_primes.push_back(prime_nums.at(j));
				sexy_primes.push_back(prime_nums.at(i));
			}
		}

	}

	std::sort(sexy_primes.begin(), sexy_primes.end());
	sexy_primes.erase(std::unique(sexy_primes.begin(), sexy_primes.end()), sexy_primes.end());


	std::vector<std::pair<int, int> > sexy_pairs;
	for (const auto& sexy_num : sexy_primes)
		for (int i = 2; i < sexy_num; ++i)
			if (sexy_num - i == 6 && std::find(sexy_primes.begin(), sexy_primes.end(), i) != sexy_primes.end())
				sexy_pairs.emplace_back(i, sexy_num);

	std::cout << "===================================\n" << 
        "sexy primes for given limit of " << limit << " is:\n";
	for (const auto& pair : sexy_pairs)
		std::cout << '(' << pair.first << ", " << pair.second << ')' << '\n';

    return EXIT_SUCCESS; 
}