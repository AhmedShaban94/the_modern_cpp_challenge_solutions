cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_75 main.cpp)
set_target_properties (problem_75 PROPERTIES FOLDER "09.Serialization")

include(FetchContent)
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
    GIT_TAG v3.10.5)

FetchContent_MakeAvailable(json)
target_link_libraries(problem_75 PRIVATE nlohmann_json::nlohmann_json)