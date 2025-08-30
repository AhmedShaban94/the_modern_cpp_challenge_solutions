cmake_minimum_required(VERSION 3.11)
project(modern_cpp_challenge_book)

# Set the minimum required version for all subdirectories
set(CMAKE_MINIMUM_REQUIRED_VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

if(MSVC)
  add_compile_options(/W3 /external:W0 /permissive- /MP)
  string(APPEND CMAKE_CXX_FLAGS " /Zc:__cplusplus")
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
      GIT_TAG        v3.4.0
  )
  FetchContent_MakeAvailable(Catch2)
  link_libraries(Catch2::Catch2WithMain)
  include_directories(${catch2_SOURCE_DIR}/single_include)
endif()

# add_executable(ALL_TESTS 
# chapter01/problem_01/tests_main.cpp

# # Chapter 1
# chapter01/problem_01/main.cpp
# chapter01/problem_02/main.cpp
# chapter01/problem_03/main.cpp
# chapter01/problem_04/main.cpp
# chapter01/problem_05/main.cpp
# chapter01/problem_06/main.cpp
# chapter01/problem_07/main.cpp
# chapter01/problem_08/main.cpp
# chapter01/problem_09/main.cpp
# chapter01/problem_10/main.cpp
# chapter01/problem_11/main.cpp
# chapter01/problem_12/main.cpp
# chapter01/problem_14/main.cpp

# # Chapter 2
# chapter02/problem_15/main.cpp
# # chapter02/problem_16/main.cpp: problem related to include directories is not resolved.
# # chapter02/problem_17/main.cpp: problem related to include directories is not resolved.
# chapter02/problem_18/main.cpp
# chapter02/problem_19/main.cpp
# chapter02/problem_20/main.cpp
# chapter02/problem_22/main.cpp

# # Chapter 3
# chapter03/problem_23/main.cpp
# chapter03/problem_24/main.cpp
# chapter03/problem_25/main.cpp
# chapter03/problem_26/main.cpp
# chapter03/problem_27/main.cpp
# chapter03/problem_28/main.cpp
# chapter03/problem_29/main.cpp
# chapter03/problem_30/main.cpp
# chapter03/problem_31/main.cpp

# # Chapter 5
# # chapter05/problem_40/main.cpp problem related to include directories is not resolved.
# # chapter05/problem_41/main.cpp problem related to include directories is not resolved.
# # chapter05/problem_42/main.cpp problem related to include directories is not resolved.
# )
# add_test(NAME ALL_TESTS COMMAND ALL_TESTS)

add_subdirectory(chapter01)
add_subdirectory(chapter02)
add_subdirectory(chapter03)
add_subdirectory(chapter04)
add_subdirectory(chapter05)
add_subdirectory(chapter09)
add_subdirectory(chapter10)