cmake_minimum_required(VERSION 3.21)

project(Game)

set(CMAKE_CXX_STANDARD 20)

set(GAME_SOURCES game.cpp)

add_library(game SHARED ${GAME_SOURCES})