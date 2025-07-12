cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

# Define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING to suppress filesystem deprecation warnings
add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)

add_executable(problem_82 src/main.cpp src/tests_main.cpp)
target_link_libraries(problem_82 PRIVATE SimZip)
set_target_properties (problem_82 PROPERTIES FOLDER "10.Archives, Images & Database")
add_test(NAME problem_82_tests COMMAND problem_82)
add_custom_command(TARGET problem_82 PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:problem_82>/data)