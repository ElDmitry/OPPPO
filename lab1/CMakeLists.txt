cmake_minimum_required(VERSION 3.5)
project(lab1)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab1 main.cpp
                    Shape2D.cpp Shape2D.h
                    Circle.cpp Circle.h
                    Rectangle.cpp Rectangle.h
                    MyHashTable.h
                    Date.cpp Date.h)