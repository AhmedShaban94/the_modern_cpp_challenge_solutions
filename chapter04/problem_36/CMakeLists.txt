cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_36 main.cpp)
set_target_properties(problem_36 PROPERTIES FOLDER "03.Streams")
target_link_libraries(problem_36 PRIVATE stdc++fs)