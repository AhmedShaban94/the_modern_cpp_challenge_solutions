cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

if(NOT WIN32)
    add_executable(problem_43 main.cpp)
    set_target_properties (problem_43 PROPERTIES FOLDER "05.Datetime")

    find_package(CURL REQUIRED)
    include( FetchContent )
        FetchContent_Declare( 
            date_src
            GIT_REPOSITORY https://github.com/HowardHinnant/date.git
            GIT_TAG        v3.0.1
        )
        FetchContent_MakeAvailable(date_src)

    target_sources(problem_43 PRIVATE ${date_src_SOURCE_DIR}/src/tz.cpp)
    target_link_libraries (problem_43 PRIVATE date::date CURL::libcurl)
endif()