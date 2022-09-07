cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

# main configuration 
add_executable(problem_07 main.cpp tests_main.cpp)
set_target_properties (problem_07 PROPERTIES FOLDER "01.Math")
add_test(NAME problem_07_tests COMMAND problem_07)