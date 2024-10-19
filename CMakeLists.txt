cmake_minimum_required(VERSION 3.10)

project(regroup-bodies)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)

target_include_directories(regroup-bodies PRIVATE lib)
