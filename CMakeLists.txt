cmake_minimum_required(VERSION 3.22.1)
project(Hex)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hex main.cpp
        Board.cpp
        Board.h
        ParseInput.cpp
        ParseInput.h
        ValidateBoard.cpp
        ValidateBoard.h
        IsGameOver.cpp
        IsGameOver.h
        CanWin.cpp
        CanWin.h
)
