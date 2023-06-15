cmake_minimum_required(VERSION 3.25)
project(flecs_crash C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCES
        "src/*.c"
        "src/*.h"
        )

add_executable(flecs_crash ${SOURCES})
