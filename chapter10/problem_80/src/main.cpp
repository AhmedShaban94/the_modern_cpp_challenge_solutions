#include <exception>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "ZipLib/ZipArchive.h"
#include "ZipLib/ZipFile.h"
#include "catch2/catch_test_macros.hpp"

void compress(std::filesystem::path destinationFile) {
  try {
  } catch (std::exception ex) {
    std::cerr << ex.what() << '\n';
  }
}

void compress(std::filesystem::path destinationDirectory) {
  try {
  } catch (std::exception ex) {
    std::cerr << ex.what() << '\n';
  }
}

void decompress(std::filesystem::path destinationDirectory) {
  try {
  } catch (std::exception ex) {
    std::cerr << ex.what() << '\n';
  }
}

// chapter-10 -> problem80 (compress/decompress files to zip)
TEST_CASE("Compressing file to zip", "[compress_file_to_zip]") {}
TEST_CASE("Compressing directory to zip", "[compress_directory_to_zip]") {}
TEST_CASE("Decompressing zip to directory", "[decompress_zip_to_directory]") {}
