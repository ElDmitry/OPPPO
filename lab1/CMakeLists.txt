cmake_minimum_required(VERSION 3.5)
project(lab1)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab1 main.cpp Shape2D.cpp Shape2D.h Shape2DTypes.cpp Shape2DTypes.h Circle.cpp Circle.h Rectangle.cpp Rectangle.h MyHashTable.h)