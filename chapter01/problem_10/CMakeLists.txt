cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

# main configuration 
add_executable(problem_10 main.cpp)
set_target_properties (problem_10 PROPERTIES FOLDER "01.Math")
add_test(NAME problem_10_tests COMMAND problem_10)