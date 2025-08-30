cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_76 src/main.cpp)
set_target_properties (problem_76 PROPERTIES FOLDER "09.Serialization")

include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)

FetchContent_MakeAvailable(json)
target_link_libraries(problem_76 PRIVATE nlohmann_json::nlohmann_json)

add_custom_command(TARGET problem_76 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:problem_76>/data)