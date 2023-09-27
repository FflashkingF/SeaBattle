cmake_minimum_required(VERSION 3.20)

project(SeaBattle)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})


add_subdirectory(Help)

add_subdirectory(Visitor)

add_subdirectory(Board)
add_dependencies(board helper visitor)
target_link_libraries(board helper visitor)

add_subdirectory(Player)
add_dependencies(player board)
target_link_libraries(player board)

add_subdirectory(FieldGenerator)
add_dependencies(generator board)
target_link_libraries(generator board)

add_subdirectory(DFS)
add_dependencies(dfs board)
target_link_libraries(dfs board)

add_subdirectory(KillChecker)
add_dependencies(killchecker board dfs)
target_link_libraries(killchecker board dfs)

add_subdirectory(Game)
add_dependencies(game player generator)
target_link_libraries(game player generator)

add_executable(SeaBattle main.cpp)
add_dependencies(SeaBattle game)
target_link_libraries(SeaBattle game)

install(TARGETS SeaBattle helper killchecker visitor board player generator dfs game
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib)