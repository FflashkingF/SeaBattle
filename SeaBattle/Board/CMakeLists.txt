cmake_minimum_required(VERSION 3.21)

project(Board)

set(CMAKE_CXX_STANDARD 20)

set(BOARD_SOURCES board.cpp dfs.cpp)

add_library(board SHARED ${BOARD_SOURCES})