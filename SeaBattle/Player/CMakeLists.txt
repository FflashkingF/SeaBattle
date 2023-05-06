cmake_minimum_required(VERSION 3.20)

project(Player)

set(CMAKE_CXX_STANDARD 20)

set(PLAYER_SOURCES player.cpp)

add_library(player SHARED ${PLAYER_SOURCES})