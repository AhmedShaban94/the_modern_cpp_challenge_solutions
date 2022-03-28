cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

include(FetchContent)
FetchContent_Declare(pdf
    GIT_REPOSITORY https://github.com/galkahana/PDF-Writer
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    GIT_TAG 4.0)
FetchContent_MakeAvailable(pdf)

# file(GLOB PDFWriter_SOURCES "${CMAKE_SOURCE_DIR}/external/pdf-src/PDFWriter/*.cpp")
add_executable(problem_77 main.cpp)
target_include_directories(problem_77 PUBLIC ${CMAKE_SOURCE_DIR}/external/pdf-src/)

target_link_libraries(problem_77 PDFWriter)
target_link_libraries(problem_77 FreeType)
target_link_libraries(problem_77 LibAesgm)
target_link_libraries(problem_77 LibJpeg)
target_link_libraries(problem_77 LibPng)
target_link_libraries(problem_77 LibTiff)
target_link_libraries(problem_77 Zlib)

set_target_properties (problem_77 PROPERTIES FOLDER "09.Serialization")