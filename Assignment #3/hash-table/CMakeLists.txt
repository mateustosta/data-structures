cmake_minimum_required(VERSION 3.17)
project(hash_table C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(hash-table
        hash-table_ds.c
        hash-table_ds.h
        main.c)
