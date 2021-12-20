cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_37 main.cpp)
set_target_properties(problem_37 PROPERTIES FOLDER "03.Streams")
target_link_libraries(problem_37 PRIVATE stdc++fs)
add_custom_command(
    TARGET problem_37 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/files
            ${CMAKE_CURRENT_BINARY_DIR}/files)