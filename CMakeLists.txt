cmake_minimum_required(VERSION 3.7.0)
project(modern_cpp_challenge_book)

option(ENABLE_TESTS "Enable tests" ON)
message("Enable testing status: ${ENABLE_TESTS}")
if(${ENABLE_TESTS})
    Include(FetchContent)
    set(FETCHCONTENT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.1
    )
    FetchContent_MakeAvailable(Catch2)
    link_libraries(Catch2::Catch2)
    include_directories(${catch2_SOURCE_DIR}/single_include)
endif()

add_subdirectory(chapter01/problem_01)
add_subdirectory(chapter01/problem_02)
add_subdirectory(chapter01/problem_03)
add_subdirectory(chapter01/problem_04)
add_subdirectory(chapter01/problem_05)
add_subdirectory(chapter01/problem_06)
add_subdirectory(chapter01/problem_07)
add_subdirectory(chapter01/problem_08)
add_subdirectory(chapter01/problem_09)
add_subdirectory(chapter01/problem_10)
add_subdirectory(chapter01/problem_11)
add_subdirectory(chapter01/problem_12)
add_subdirectory(chapter01/problem_13)
add_subdirectory(chapter01/problem_14)