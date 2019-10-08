cmake_minimum_required(VERSION 3.7)
project(ACA_II_Monte_Carlo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ACA_II.cpp)
add_executable(ACA_II_Monte_Carlo ${SOURCE_FILES})