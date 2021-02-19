cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

# main configuration 
add_executable(problem_13 main.cpp)
target_compile_options(problem_13 PRIVATE -O3)
target_compile_definitions(problem_13 PRIVATE cxx_std_17) 
set_target_properties (problem_13 PROPERTIES FOLDER "01.Math")