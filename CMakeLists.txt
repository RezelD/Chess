cmake_minimum_required(VERSION 3.31)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 Main.cpp
        Board.cpp
        Board.h
        InputHandler.cpp
        InputHandler.h
        Move.cpp
        Move.h
        Pieces.h
)


