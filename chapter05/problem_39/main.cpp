#include <chrono>
#include <iostream>
#include <limits>

template <typename clock_t, typename duration_t>
class Timer
{
private:
    std::chrono::time_point<clock_t> start;

public:
    Timer() : start{clock_t::now()} {}
    ~Timer()
    {
        const auto end = clock_t::now();
        std::cout << std::chrono::duration_cast<duration_t>(end - start).count() << '\n';
    }
};

void func()
{
    Timer<std::chrono::system_clock, std::chrono::milliseconds> t{};
    for (std::size_t i{0}; i < INT16_MAX; ++i)
        std::cout << i << '\n';
}

int main()
{
    return EXIT_SUCCESS;
}