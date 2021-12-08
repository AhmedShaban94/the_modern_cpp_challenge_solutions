cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_34 main.cpp)
set_target_properties(problem_34 PROPERTIES FOLDER "03.Streams")
add_custom_command(
        TARGET problem_34 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/file.txt
                ${CMAKE_CURRENT_BINARY_DIR}/file.txt)