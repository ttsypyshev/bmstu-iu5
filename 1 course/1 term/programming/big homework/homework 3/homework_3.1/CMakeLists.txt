cmake_minimum_required(VERSION 3.23)
project(homework_3_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(homework_3_1 main.c)

MATH(EXPR stack_size "64 * 1024 * 1024") # 64 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")