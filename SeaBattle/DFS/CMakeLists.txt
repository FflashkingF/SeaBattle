cmake_minimum_required(VERSION 3.21)

project(DFS)

set(CMAKE_CXX_STANDARD 20)

set(DFS_SOURCES dfs.cpp)

add_library(dfs SHARED ${DFS_SOURCES})