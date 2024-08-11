cmake_minimum_required(VERSION 3.25)
project(practice_01)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(practice_01 sources/main.cpp)

include(FindPkgConfig)
find_package(MyLib REQUIRED)
include_directories(${MYLIB_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${MYLIB_LIBRARY})