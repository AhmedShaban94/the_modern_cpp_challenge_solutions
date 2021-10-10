if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE
      "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      CACHE STRING "")
endif()

cmake_minimum_required(VERSION 3.7.0)
project(modern_cpp_challenge_book)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
if(MSVC)
  add_compile_options(/O2 /W3 /permissive)
else()
  add_compile_options(-O3 -Wall -Wextra -pedantic)
endif()

option(ENABLE_TESTS "Enable tests" ON)
message("Enable testing status: ${ENABLE_TESTS}")
if(${ENABLE_TESTS})
  enable_testing()
  find_package(Catch2 REQUIRED)
  link_libraries(Catch2::Catch2)
endif()

add_subdirectory(chapter01)
add_subdirectory(chapter02)
add_subdirectory(chapter03)
