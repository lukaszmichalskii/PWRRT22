cmake_minimum_required(VERSION 3.16)
project(Kernals)

set(CMAKE_CXX_STANDARD 14)

add_executable(Kernals main.cpp graphx/digraph.cpp graphx/digraph.h graphx/edge.cpp graphx/edge.h algorithm/cost_function.h algorithm/backtracking.h algorithm/tkp.h algorithm/utilities.h)
