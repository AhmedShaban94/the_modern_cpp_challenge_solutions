#include <iostream> 

//Chapter-1 -> problem 1  (sum of divisable numbers on 3 or 5)
int main() 
{
    unsigned int limit;
	std::vector<int> vec;

	std::cout << "Enter the limit.\nNote: The limit is included\n";
	std::cin >> limit;

	for (int i = 3; i <= limit; ++i)
		if (i % 3 == 0 || i % 5 == 0)
			vec.push_back(i);

	std::cout << "sum: " << std::accumulate(vec.begin(), vec.end(), 0) << '\n';
    return EXIT_SUCCESS; 
}