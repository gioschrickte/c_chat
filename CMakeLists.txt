cmake_minimum_required(VERSION 3.28.3)
project(c_chat C)
set(CMAKE_C_STANDARD 11)

find_package(Threads REQUIRED)

add_executable(client src/client.c)
add_executable(server src/server.c)

target_link_libraries(client PUBLIC Threads::Threads)
target_link_libraries(server PUBLIC Threads::Threads)