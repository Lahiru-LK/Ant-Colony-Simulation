cmake_minimum_required(VERSION 3.25)
project(AntColony C)

set(CMAKE_C_STANDARD 11)

add_executable(AntColony main.c colony.c)
