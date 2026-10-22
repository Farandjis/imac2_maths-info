cmake_minimum_required(VERSION 3.15)

project(zero)

# file to comile
add_executable(zero src/main.cpp)

# compilation options
target_compile_features(zero PRIVATE cxx_std_20) 

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # using Clang
    message(STATUS "compiling with clang")
    target_compile_options(zero PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wno-unknown-warning-option -Wno-unused-private-field)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # using GCC
    message(STATUS "compiling with GCC")
    target_compile_options(zero PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors -Wno-unknown-warning-option -Wno-comment)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    message(STATUS "compiling with intel")
    # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # using Visual Studio C++
    message(STATUS "compiling with MSVC")
    target_compile_options(zero PRIVATE /W3)
endif()
