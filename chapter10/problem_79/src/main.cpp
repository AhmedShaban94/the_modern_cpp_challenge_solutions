#include <iostream>

#include "zip_file.hpp"

int main() {
  std::string filepath = "";
  miniz_cpp::zip_file file{filepath};

  std::cout << file.get_filename() << '\n';

  return EXIT_SUCCESS;
}