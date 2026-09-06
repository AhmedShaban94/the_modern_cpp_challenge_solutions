cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

# Fetch SimZip on every platform so its headers are available to clangd and
# other tooling, but only build the problem_80 target on Linux.
include(FetchContent)
FetchContent_Declare(
    SimZip
    GIT_REPOSITORY https://github.com/L-Super/SimZip.git
    GIT_TAG v0.9.0)
FetchContent_MakeAvailable(SimZip)

if (LINUX)
    add_executable(problem_80 src/main.cpp src/tests_main.cpp)
    target_link_libraries(problem_80 PRIVATE SimZip)
    set_target_properties (problem_80 PROPERTIES FOLDER "10.Archives, Images & Database")
    add_test(NAME problem_80_tests COMMAND problem_80)
    add_custom_command(TARGET problem_80 PRE_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:problem_80>/data)
endif()