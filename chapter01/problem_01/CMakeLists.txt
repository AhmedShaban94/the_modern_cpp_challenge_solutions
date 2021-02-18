cmake_minimum_required(VERSION 3.11.0)
project(modern_cpp_challenge_book)

# main configuration 
add_executable(main main.cpp)
target_compile_options(main PRIVATE -O3)
target_compile_definitions(main PRIVATE cxx_std_17) 
set_target_properties (main PROPERTIES FOLDER "01.Math")

#tests configuration
if(${ENABLE_TESTS})
	add_executable(tests tests.cpp)
	target_include_directories(tests PRIVATE ../../include/)
	target_compile_features(tests PRIVATE cxx_std_17)
endif()
