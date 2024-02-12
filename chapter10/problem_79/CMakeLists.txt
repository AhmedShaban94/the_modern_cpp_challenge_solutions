cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_79 src/main.cpp)
target_include_directories(problem_79 PRIVATE include)
set_target_properties (problem_79 PROPERTIES FOLDER "10.Archives, Images & Database")

# add_custom_command(TARGET problem_73 PRE_BUILD
#                    COMMAND ${CMAKE_COMMAND} -E copy_directory
#                    ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:problem_73>/data)
