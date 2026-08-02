cmake_minimum_required(VERSION 3.28.3)
project(HttpServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        HttpServer src/main.cpp
        src/server.h
        src/httpParser.cpp
        src/router.cpp
        src/router.h
        src/httpParser.h
        src/server.cpp
)
