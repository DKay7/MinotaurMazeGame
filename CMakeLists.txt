cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


project(minotaur_maze_game)


find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_subdirectory(src)
