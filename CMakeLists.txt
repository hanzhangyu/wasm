cmake_minimum_required(VERSION 3.14)
project(wasm C)

set(CMAKE_C_STANDARD 99)

add_executable(wasm src/hello/hello.c)