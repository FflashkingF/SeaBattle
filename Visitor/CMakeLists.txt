cmake_minimum_required(VERSION 3.20)

project(Visitor)

set(CMAKE_CXX_STANDARD 20)

set(VISITOR_SOURCES visitor.cpp)

add_library(visitor SHARED ${VISITOR_SOURCES})