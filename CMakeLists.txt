cmake_minimum_required(VERSION 3.21)
project(project2 C)

set(CMAKE_C_STANDARD 11)

add_executable(project2 main.c twitter_create.c twitter_create.h printing.c printing.h functionality.c functionality.h)