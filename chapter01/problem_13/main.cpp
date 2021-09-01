#include <algorithm>
#include <bitset>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <functional>
#include <array>

template <
    typename Engine = std::mt19937_64,
    typename Distribution = std::uniform_real_distribution<>>
double compute_PI(Engine &eng, Distribution &dist, const std::size_t &samples = 1000000)
{
    std::size_t hit{0};
    for (std::size_t i{0}; i < samples; ++i)
    {
        auto x = dist(eng);
        auto y = dist(eng);
        if (y <= std::sqrt(1 - std::pow(x, 2)))
            hit += 1;
    }
    return 4.0 * hit / samples;
}

int main()
{
    std::random_device rd{};
    auto seed_data = std::array<std::size_t, std::mt19937_64::state_size>{};
    std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
    std::seed_seq seq(seed_data.begin(), seed_data.end());
    auto engine = std::mt19937_64{seq};
    auto dist = std::uniform_real_distribution<> { 0, 1 };
    for (std::size_t i = 0; i < 20; i++)
        std::cout << compute_PI(engine, dist) << '\n';
    return EXIT_SUCCESS;
}