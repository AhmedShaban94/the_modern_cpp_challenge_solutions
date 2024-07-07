cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

if (NOT WIN32)
    add_executable(problem_79 src/main.cpp src/tests_main.cpp)
    target_link_libraries(problem_79 PRIVATE ZipLib)
    target_include_directories(problem_79 PRIVATE ../ZipLib)
    set_target_properties (problem_79 PROPERTIES FOLDER "10.Archives, Images & Database")
    add_test(NAME problem_79_tests COMMAND problem_79)
    add_custom_command(TARGET problem_79 PRE_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:problem_79>/data)
endif()