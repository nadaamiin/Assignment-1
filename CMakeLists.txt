cmake_minimum_required(VERSION 3.27)
project(lastVole)

set(CMAKE_CXX_STANDARD 23)

add_executable(lastVole A1-Task4-S21-20230440-20230560-20231088.cpp
        CPU.cpp
        CU.cpp
        MainUI.cpp
        Memory.cpp
        Register.cpp
        ALU.cpp)
