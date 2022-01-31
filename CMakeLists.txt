cmake_minimum_required(VERSION 3.11)
project(modern_cpp_challenge_book)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

if(MSVC)
  add_compile_options(/W3 /permissive-)
else()
  add_compile_options(-O3 -Wall -Wextra -pedantic)
endif()

option(ENABLE_TESTING "Enable tests" ON)
message("Enable testing status: ${ENABLE_TESTING}")
if(${ENABLE_TESTING})
  enable_testing()
  Include(FetchContent)
  set(FETCHCONTENT_QUIET off)
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

add_subdirectory(chapter01)
add_subdirectory(chapter02)
add_subdirectory(chapter03)
add_subdirectory(chapter04)
add_subdirectory(chapter05)
add_subdirectory(chapter09)
