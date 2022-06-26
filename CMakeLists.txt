cmake_minimum_required(VERSION 3.21)
project(GraphAlgorithms C)

set(CMAKE_C_STANDARD 23)

add_executable(GraphAlgorithms main.c algs1.c algs2.c mgraph.c graph.c)
