#include <chrono>
#include <iostream>
#include <limits>
#include <thread>
#include <type_traits>

template <typename clock_t, typename duration_t>
class Timer {
 private:
  std::chrono::time_point<clock_t> m_start;
  std::string m_functionName{};

 public:
  Timer() : m_start{clock_t::now()} {}
  Timer(const std::string& functionName) : m_start{clock_t::now()}, m_functionName{functionName} {}

  ~Timer() {
    const auto end = clock_t::now();
    const auto duration = std::chrono::duration_cast<duration_t>(end - m_start).count();
    std::cout << (m_functionName.empty() ? std::string{"Execution Time: "}
                                         : std::string{"Execution time of function {"} + m_functionName + "}: ");
    std::cout << duration;
    if (std::is_same_v<std::chrono::seconds, duration_t>)
      std::cout << " sec.\n";
    else if (std::is_same_v<std::chrono::milliseconds, duration_t>)
      std::cout << " ms.\n";
    else if (std::is_same_v<std::chrono::microseconds, duration_t>)
      std::cout << " µs\n";
    else if (std::is_same_v<std::chrono::nanoseconds, duration_t>)
      std::cout << " ns\n";
  }
};

void func() {
  using namespace std::chrono_literals;
  Timer<std::chrono::system_clock, std::chrono::milliseconds> t{};
  std::this_thread::sleep_for(5s);
}

int main() {
  func();
  return EXIT_SUCCESS;
}