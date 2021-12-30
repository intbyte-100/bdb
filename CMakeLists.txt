cmake_minimum_required(VERSION 3.19)




set(CMAKE_C_STANDARD 11)


project(bdb7)

include_directories(bdb7 src)

add_executable(bdb7
        main.c
        src/array.h
        src/array.c
        src/list.h
        src/list.c
)
