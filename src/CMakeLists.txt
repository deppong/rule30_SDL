cmake_minimum_required(VERSION 3.7)

project(c-automata)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(c-automata main.c)
target_link_libraries(c-automata ${SDL2_LIBRARIES})