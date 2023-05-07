cmake_minimum_required(VERSION 3.20)

project(FieldGenerator)

set(CMAKE_CXX_STANDARD 20)

set(FIELD_GENERATOR_SOURCES generator.cpp)

add_library(generator SHARED ${FIELD_GENERATOR_SOURCES})