cmake_minimum_required(VERSION 3.13)


# give a name to the project
project(td1 LANGUAGES C CXX)

# files to compile
add_executable(td1 src/seeFloat.cpp)

# compilation options
target_compile_features(td1 PRIVATE cxx_std_11) # use at least c++ 11
if (MSVC)
    target_compile_options(td1 PRIVATE /W3)
else()
    target_compile_options(td1 PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()


