cmake_minimum_required(VERSION 3.23)
project(inf_lab_4)

set(CMAKE_CXX_STANDARD 20)

add_executable(inf_lab_4 sources/main.cpp sources/Iteration.cpp sources/Bisection.cpp sources/Newton.cpp include/lab04.hpp)
