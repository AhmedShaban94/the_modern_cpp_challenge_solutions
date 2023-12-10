#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

enum class STATUS { RUNNING, SUSPENDED };
enum class PLATFORM { x32_BIT, x64_BIT };

struct ProcessInfo {
    std::string name;
    std::size_t pid;
    STATUS status;
    std::string accountName;
    std::size_t memorySize;
    PLATFORM platform;
};

std::ostream& operator<<(std::ostream& os, const ProcessInfo& info) {
    os << std::left << std::setw(25) << std::setfill(' ') << info.name;
    os << std::left << std::setw(8) << std::setfill(' ')
       << (info.status == STATUS::RUNNING ? "Running" : "Suspended") << '\t';
    os << std::left << std::setw(12) << std::setfill(' ') << info.accountName
       << '\t';
    os << std::right << std::setw(15) << std::setfill(' ') << info.memorySize
       << '\t';
    os << std::left << std::setw(10) << std::setfill(' ')
       << (info.platform == PLATFORM::x32_BIT ? "32-bit" : "64-bit");

    return os;
}

void printProcesses(std::vector<ProcessInfo> processes) {
    std::sort(processes.begin(), processes.end(),
              [](const auto& first, const auto& second) {
                  return first.name < second.name;
              });
    for (const auto& p : processes)
        std::cout << p << '\n';
}

int main() {
    std::vector<ProcessInfo> processes{
        {"chrome.exe", 1044, STATUS::RUNNING, "ahmed.shaban", 25180,
         PLATFORM::x32_BIT},
        {"explorer.exe", 7108, STATUS::RUNNING, "ahmed.shaban", 29529,
         PLATFORM::x64_BIT},
        {"chrome.exe", 10100, STATUS::RUNNING, "ahmed.shaban", 227756,
         PLATFORM::x32_BIT},
        {"cmd.exe", 512, STATUS::RUNNING, "SYSTEM", 48, PLATFORM::x64_BIT},
        {"skype.exe", 22456, STATUS::SUSPENDED, "ahmed.shaban", 656,
         PLATFORM::x64_BIT}};
    printProcesses(processes);
    return EXIT_SUCCESS;
}