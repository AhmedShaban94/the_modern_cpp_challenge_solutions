#include <algorithm>
#include <iostream>
#include <regex>
#include <vector>

#include "filesystem.h"

namespace fs = std::filesystem;

std::vector<fs::path> findFilesWithRegex(const std::string& directory, const std::string& regexp) {
  const std::regex rgx{regexp};
  std::vector<fs::path> out;
  for (const auto& path : fs::directory_iterator{directory})
    if (std::regex_match(path.path().filename().string(), rgx)) out.emplace_back(path);
  return out;
}

int main() {
  const auto out = findFilesWithRegex("files", "abc.*");
  for (const auto& e : out) std::cout << e.filename().string() << '\n';
  return EXIT_SUCCESS;
}