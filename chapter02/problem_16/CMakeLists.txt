
cmake_minimum_required (VERSION 3.11.0) 
project(modern_cpp_challenge_book)

add_executable(problem_16 main.cpp)
target_include_directories(problem_16 PRIVATE ../problem_15)
set_target_properties (problem_16 PROPERTIES FOLDER "02.Language")