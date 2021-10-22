cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_28 main.cpp tests_main.cpp)
set_target_properties(problem_28 PROPERTIES FOLDER "03.Strings")
add_test(NAME problem_28_tests COMMAND problem_28)
