cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_35 main.cpp)
set_target_properties(problem_35 PROPERTIES FOLDER "03.Streams")
target_link_libraries(problem_35 PRIVATE stdc++fs)