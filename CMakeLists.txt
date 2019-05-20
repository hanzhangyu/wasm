cmake_minimum_required(VERSION 3.14)
project(wasm C)

set(CMAKE_C_STANDARD 99)

add_executable(hello src/hello/hello.c)
add_executable(fs src/fs/fs.c)