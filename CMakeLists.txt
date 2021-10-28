cmake_minimum_required(VERSION 3.20)
project(RB_Tree)

set(CMAKE_CXX_STANDARD 14)

add_executable(RB_Tree main.cpp RB_Tree.cpp RB_Tree.h Node.cpp Node.h)
