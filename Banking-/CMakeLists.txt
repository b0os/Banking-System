cmake_minimum_required(VERSION 3.21)
project(Banking_)

set(CMAKE_CXX_STANDARD 14)

add_executable(Banking_ main.cpp sqlite/sqlite3.c sqlite/sqlite3.h)
