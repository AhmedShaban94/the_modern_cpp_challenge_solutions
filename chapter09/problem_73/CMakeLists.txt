cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

add_executable(problem_73 src/main.cpp src/pugixml.cpp)
target_include_directories(problem_73 PRIVATE include/)
set_target_properties (problem_73 PROPERTIES FOLDER "09.Serialization")

add_custom_command(TARGET problem_73 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:problem_73>/data)
# something is wrong with FetchConent approach in this context.
# include(FetchContent)
# FetchContent_Declare(
#         pugixml 
#         GIT_REPOSITORY https://github.com/zeux/pugixml
#         GIT_TAG v1.11
#     )
# set(PUGIXML_NO_XPATH ON CACHE INTERNAL "")
# FetchContent_MakeAvailable(pugixml)
# target_link_libraries(problem_73 PRIVATE pugixml::static)