cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_74 src/main.cpp src/pugixml.cpp)
target_include_directories(problem_74 PRIVATE include)
set_target_properties (problem_74 PROPERTIES FOLDER "09.Serialization")

add_custom_command(TARGET problem_74 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:problem_74>/data)