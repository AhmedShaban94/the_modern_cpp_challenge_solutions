#include <exception>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "ZipLib/ZipArchive.h"
#include "ZipLib/ZipFile.h"
#include "catch2/catch_test_macros.hpp"

std::vector<std::string> FindFilesInZip(std::string_view regexPattern) {
  std::vector<std::string> fileNames{};
  try {
    auto archive = ZipFile::Open(std::string{"data/sample79.zip"});
    fileNames.reserve(archive->GetEntriesCount());
    for (size_t i = 0; i < archive->GetEntriesCount(); ++i) {
      auto fileName = archive->GetEntry(i)->GetName();
      if (std::regex_match(fileName, std::regex{regexPattern.data()})) {
        fileNames.push_back(fileName);
      }
    }
  } catch (std::exception& ex) {
    std::cout << ex.what() << '\n';
  }
  return fileNames;
}

// chapter-10 -> problem79 (Finding files in a ZIP archive)
TEST_CASE("Finding files in zip file with specific pattern", "[find_files_in_zip]") {
  std::string expectedRegexPattern{"^.*\\.jpg$"};
  std::string faultyRegexPattern{"^.*\\.png$"};
  std::string faultyFileName {"mark_twain.jpg"};
  std::vector<std::string> expectedFileNames = {"albert einstein.jpg", "einstein_nobel.jpg",
                                                "Stephen_Hawking.StarChild.jpg", "Isaac_Newton.jpg"};
  
  REQUIRE(FindFilesInZip(expectedRegexPattern) == expectedFileNames);
  REQUIRE(FindFilesInZip(faultyRegexPattern).empty());
  REQUIRE(FindFilesInZip(faultyFileName).empty());
}