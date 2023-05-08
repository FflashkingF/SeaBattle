cmake_minimum_required(VERSION 3.20)

project(KillChecker)

set(CMAKE_CXX_STANDARD 20)

set(KILL_CHECKER_SOURCES killchecker.cpp)

add_library(killchecker SHARED ${KILL_CHECKER_SOURCES})
