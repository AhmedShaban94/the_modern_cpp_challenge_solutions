#include <chrono>
#include <iostream>
#include <thread>

#include "filesystem.h"

namespace fs = std::filesystem;
using namespace std::chrono_literals;

template <typename Duration>
bool is_older_than(const fs::path& path, const Duration& duration) {
  const auto entryDuration = fs::last_write_time(path).time_since_epoch();
  const auto nowDuration = (std::chrono::system_clock::now() - duration).time_since_epoch();
  return std::chrono::duration_cast<Duration>(nowDuration - entryDuration).count() > 0;
}

template <typename Duration>
void deleteFilesOlderThanDuration(const std::string& directory, const Duration& duration) {
  const fs::path path{directory};
  if (fs::exists(path)) {
    if (is_older_than(path, duration))
      fs::remove_all(path);
    else {
      for (const auto& entry : fs::recursive_directory_iterator(path))
        if (fs::is_regular_file(entry) and is_older_than(entry, duration)) {
          fs::remove(entry);
        }
    }
  } else
    throw std::runtime_error{"File not found!!!"};
}

int main() {
  try {
    deleteFilesOlderThanDuration("test", 1s);
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << '\n';
  }
  return EXIT_SUCCESS;
}