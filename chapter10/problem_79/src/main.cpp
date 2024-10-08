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

std::vector<std::string> FindFilesInZip(std::string_view regex_pattern) {
  std::vector<std::string> file_names{};
  std::regex pattern{regex_pattern.data()};

  try {
    const std::string zip_file_path = "data/sample79.zip";
    const std::string output_dir = "zip_output";
    SimZip zip(zip_file_path, SimZip::OpenMode::Read);

    zip.extractall(output_dir);
    for (const auto& entry : std::filesystem::recursive_directory_iterator("zip_output")) {
      const std::string file_name = entry.path().filename().string();
      if (entry.is_regular_file() && std::regex_search(file_name, pattern)) {
        file_names.push_back(file_name);
      }
    }
  } catch (std::exception& ex) {
    std::cout << "Error: " << ex.what() << '\n';
  }
  return file_names;
}

// chapter-10 -> problem79 (Finding files in a ZIP archive)
TEST_CASE("Finding files in zip file with specific pattern", "[find_files_in_zip]") {
  std::string expected_regex_pattern{"^.*\\.jpg$"};
  std::string faulty_regex_pattern{"^.*\\.png$"};
  std::string faulty_file_name{"mark_twain.jpg"};
  std::vector<std::string> expected_file_names = {"albert einstein.jpg", "einstein_nobel.jpg",
                                                "Stephen_Hawking.StarChild.jpg", "Isaac_Newton.jpg"};

  CHECK_THAT(FindFilesInZip(expected_regex_pattern), Catch::Matchers::UnorderedEquals(expected_file_names));
  CHECK(FindFilesInZip(faulty_regex_pattern).empty());
  CHECK(FindFilesInZip(faulty_file_name).empty());
}