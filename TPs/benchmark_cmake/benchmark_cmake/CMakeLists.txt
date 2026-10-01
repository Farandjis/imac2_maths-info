cmake_minimum_required(VERSION 3.13)


# give a name to the project
project(benchmark LANGUAGES C CXX)

# include Eigen
find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "lib EIGEN3 found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
else()
    message(FATAL_ERROR "lib EIGEN3 not found")
endif()


# files to compile
add_executable(benchmark src/benchmark.cpp)

# compilation options
target_compile_features(benchmark PRIVATE cxx_std_17) # use at least c++ 11
if (MSVC)
    target_compile_options(benchmark PRIVATE /W3)
else()
    target_compile_options(benchmark PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()

# lib include path
target_include_directories(benchmark PRIVATE "${EIGEN3_INCLUDE_DIR}")

find_package(OpenMP) 
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    target_link_libraries(benchmark OpenMP::OpenMP_CXX)
endif()