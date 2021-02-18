cmake_minimum_required(VERSION 3.7.0)
project(modern_cpp_challenge_book)

option(ENABLE_TESTS "Enable tests" ON)
if (${ENABLE_TESTS})
    enable_testing()
endif()

add_subdirectory(chapter01/problem_01)
add_subdirectory(chapter01/problem_02)
add_subdirectory(chapter01/problem_03)
add_subdirectory(chapter01/problem_04)