cmake_minimum_required(VERSION 3.23)
project(inf_lab_05)

set(CMAKE_CXX_STANDARD 14)

add_executable(inf_lab_05 sources/main.cpp include/all_functios.h sources/other_functions.cpp sources/Method_Bubble.cpp sources/Method_MInMax.cpp)
