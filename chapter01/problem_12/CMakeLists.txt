cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

# main configuration 
add_executable(problem_12 main.cpp)
target_compile_options(problem_12 PRIVATE -O3)
target_compile_definitions(problem_12 PRIVATE cxx_std_17) 
set_target_properties (problem_12 PROPERTIES FOLDER "01.Math")