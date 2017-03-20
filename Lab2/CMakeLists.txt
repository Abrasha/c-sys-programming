cmake_minimum_required(VERSION 3.5.1)
project(Lab2)

SET(GCC_COVERAGE_COMPILE_FLAGS "-ansi -pedantic -Wall -Werror")

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES task1.c)
add_executable(Lab2 ${SOURCE_FILES})