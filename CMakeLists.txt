cmake_minimum_required(VERSION 4.0)
project(c_chat C)

set(CMAKE_C_STANDARD 11)

add_executable(client src/client.c)

add_executable(server src/server.c)