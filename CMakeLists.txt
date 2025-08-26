cmake_minimum_required(VERSION 3.5)
project(C_List C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(C_List
        c_list.h
        test.c)
