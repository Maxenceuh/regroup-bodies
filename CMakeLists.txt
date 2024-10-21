cmake_minimum_required(VERSION 3.10)

project(MonProjet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib)

add_library(regroup STATIC ${CMAKE_SOURCE_DIR}/include/regroup/regroup.cpp)

add_executable(regroup-bodies.out ${CMAKE_SOURCE_DIR}/src/main.cpp)

target_link_libraries(regroup-bodies.out PRIVATE regroup)
