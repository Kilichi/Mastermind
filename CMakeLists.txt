cmake_minimum_required(VERSION 3.26)
project(Mastermind)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(Mastermind main.cpp
        MasterMind.h
)
