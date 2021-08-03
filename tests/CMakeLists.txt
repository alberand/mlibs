cmake_minimum_required(VERSION 3.13.1)

project(circbuf-tests)

find_library(CIRCBUFLIB circbuf ../build)
find_library(MATCHBUFLIB matchbuf ../build)

include_directories(../)

add_executable(tests tests.c)
set (CMAKE_C_FLAGS "-ggdb")
target_link_libraries(tests ${CIRCBUFLIB} ${MATCHBUFLIB})
