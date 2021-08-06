
cmake_minimum_required (VERSION 3.11.0) 
project(modern_cpp_challenge_book)

add_executable(problem_15 tests_main.cpp main.cpp)
set_target_properties (problem_15 PROPERTIES FOLDER "02.Language")