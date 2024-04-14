#include <iostream>

#include "ZipLib/ZipFile.h"
#include "ZipLib/ZipArchive.h"

int main() {
// open archive file. 
auto archive = ZipFile::Open(std::string{"data/sample79.zip"});
std::cout << archive->GetEntriesCount() << '\n'; 


// enumrate through the archive object. 
// list the files that only matches the regex. 

  return EXIT_SUCCESS;
}