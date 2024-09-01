#include <exception>
#include <filesystem>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "SimZip.h"
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_vector.hpp"

std::vector<std::string> FindFilesInZip(std::string_view regexPattern) {
  std::vector<std::string> fileNames{};
  std::regex pattern(regexPattern.data());

  std::cout << "Directory: " << std::filesystem::current_path() << '\n';

  try {
    const std::string zipFilePath = "data/sample79.zip";
    const std::string outputDir = "zip_output";
    SimZip zip(zipFilePath, SimZip::OpenMode::Read);

    zip.extractall(outputDir);
    for (const auto& entry : std::filesystem::recursive_directory_iterator("zip_output")) {
      const std::string fileName = entry.path().filename().string();
      if (entry.is_regular_file() && std::regex_search(fileName, pattern)) {
        fileNames.push_back(fileName);
      }
    }
  } catch (std::exception& ex) {
    std::cout << "Error: " << ex.what() << '\n';
  }
  return fileNames;
}

// chapter-10 -> problem79 (Finding files in a ZIP archive)
TEST_CASE("Finding files in zip file with specific pattern", "[find_files_in_zip]") {
  std::string expectedRegexPattern{"^.*\\.jpg$"};
  std::string faultyRegexPattern{"^.*\\.png$"};
  std::string faultyFileName{"mark_twain.jpg"};
  std::vector<std::string> expectedFileNames = {"albert einstein.jpg", "einstein_nobel.jpg",
                                                "Stephen_Hawking.StarChild.jpg", "Isaac_Newton.jpg"};

  CHECK_THAT(FindFilesInZip(expectedRegexPattern), Catch::Matchers::UnorderedEquals(expectedFileNames));
  CHECK(FindFilesInZip(faultyRegexPattern).empty());
  CHECK(FindFilesInZip(faultyFileName).empty());
}