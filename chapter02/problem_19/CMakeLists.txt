cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_19 main.cpp tests_main.cpp)
set_target_properties(problem_19 PROPERTIES FOLDER "02.Language")
add_test(NAME problem_19_tests COMMAND problem_19)
