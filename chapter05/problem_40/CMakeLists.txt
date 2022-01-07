cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_40 main.cpp tests_main.cpp)
set_target_properties (problem_40 PROPERTIES FOLDER "05.Datetime")
add_test(NAME problem_40_tests COMMAND problem_40)

include( FetchContent )
    FetchContent_Declare( 
        date_src
        GIT_REPOSITORY https://github.com/HowardHinnant/date.git
        GIT_TAG        v3.0.1
    )
    FetchContent_MakeAvailable(date_src)
target_link_libraries (problem_40 PRIVATE date::date)