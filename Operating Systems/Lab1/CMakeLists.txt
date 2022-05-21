cmake_minimum_required(VERSION 3.21)
project(Lab1)

set(CMAKE_CXX_STANDARD 98)

add_executable(main main.cpp Employee.h)
add_executable(creator Creator.cpp Employee.h)
add_executable(reporter Reporter.cpp Employee.h)
