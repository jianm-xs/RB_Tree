cmake_minimum_required(VERSION 3.21)
project(RB_Tree)

set(CMAKE_CXX_STANDARD 14)

add_executable(RB_Tree RB_Node.cpp RB_Node.h RB_Tree.cpp RB_Tree.h main.cpp)
