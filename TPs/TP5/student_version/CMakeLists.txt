cmake_minimum_required(VERSION 3.15)

project(autodiff)

# file to comile
add_executable(autodiff src/main.cpp src/DualNumber.hpp)

# compilation options
target_compile_features(autodiff PRIVATE cxx_std_11) # use at least c++ 11
if (MSVC)
    target_compile_options(autodiff PRIVATE /W3)
else()
    target_compile_options(autodiff PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()

