#include <exception>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "SimZip.h"
#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_vector.hpp"

void compress(std::filesystem::path destination_dir) {
  try {
  } catch (std::exception ex) {
    std::cerr << ex.what() << '\n';
  }
}

void decompress(std::filesystem::path destination_dir) {
  try {
    const std::string zip_file_path = "data/to_decompress.zip";
    SimZip zip(zip_file_path, SimZip::OpenMode::Read);
    zip.extractall(destination_dir.string());
  } catch (std::exception& ex) {
    std::cout << "Error: " << ex.what() << '\n';
  }
}

// chapter-10 -> problem80 (compress/decompress files to zip)
TEST_CASE("Compressing directory to zip", "[compress_directory_to_zip]") {}
TEST_CASE("Decompressing zip to directory", "[decompress_zip_to_directory]") {
  const std::string kDecompressionOutputDir = "decompression_output";
  std::vector<std::string> found_filenames = {};
  std::vector<std::string> expected_filenames = {"albert einstein.jpg", "einstein_nobel.jpg",
                                                 "Stephen_Hawking.StarChild.jpg", "Isaac_Newton.jpg"};
  decompress(kDecompressionOutputDir);

  for (const auto& entry : std::filesystem::recursive_directory_iterator(kDecompressionOutputDir)) {
    if (std::filesystem::is_regular_file(entry)) {
      found_filenames.push_back(entry.path().filename().string());
    }
  }

  CHECK_THAT(found_filenames, Catch::Matchers::UnorderedEquals(expected_filenames));
}
