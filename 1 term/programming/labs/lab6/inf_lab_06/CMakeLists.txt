cmake_minimum_required(VERSION 3.23)
project(inf_lab_06)

set(CMAKE_CXX_STANDARD 14)

add_executable(inf_lab_06 sources/Main.cpp sources/Method_Integration_Rectangle.cpp sources/Method_Integration_Trapezoid.cpp sources/Other_Functions.cpp include/All_functios.h)
