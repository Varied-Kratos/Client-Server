cmake_minimum_required(VERSION 3.5)
project(Chat C)

add_executable(Server server.c util.c)
add_executable(Client client.c util.c)
