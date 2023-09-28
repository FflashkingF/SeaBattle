cmake_minimum_required(VERSION 3.21)

project(Help)

set(CMAKE_CXX_STANDARD 20)

set(HELP_SOURCES help.cpp)

add_library(helper SHARED ${HELP_SOURCES})