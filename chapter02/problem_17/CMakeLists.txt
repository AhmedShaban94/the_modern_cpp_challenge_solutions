
cmake_minimum_required (VERSION 3.11.0) 
project(modern_cpp_challenge_book)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_executable(problem_17 tests.cpp tests_main.cpp)
    set_target_properties (problem_17 PROPERTIES FOLDER "02.Language")
endif()