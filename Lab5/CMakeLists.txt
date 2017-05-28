cmake_minimum_required(VERSION 3.7)
project(Lab5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        build.sh
        constants.c
        constants.h
        crc16_apple.c
        lab5.c
        Readme.md
        reciever.c
        reciever.h
        transmitter.c
        transmitter.h
        utility.c
        utility.h)

add_executable(Lab5 ${SOURCE_FILES})