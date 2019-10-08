cmake_minimum_required(VERSION 3.7)
project(PMF)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Pr_err.cpp)
add_executable(PMF ${SOURCE_FILES})