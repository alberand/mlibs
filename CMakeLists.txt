cmake_minimum_required(VERSION 3.13.1)

project(circbuf)

set (CMAKE_C_FLAGS "-ggdb")
add_library(circbuf circbuf.c)
add_library(matchbuf matchbuf.c)
