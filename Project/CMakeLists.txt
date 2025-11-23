cmake_minimum_required(VERSION 3.10)
project(PingPong C)

set(CMAKE_C_STANDARD 11)

add_executable(server Server.c Error.c)
add_executable(client Client.c Error.c)