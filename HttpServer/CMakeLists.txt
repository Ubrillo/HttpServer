cmake_minimum_required(VERSION 4.2)
project(HttpServer)

set(CMAKE_CXX_STANDARD 20)

add_executable(HttpServer src/main.cpp
        src/server/server.cpp
        src/server/server.h
        src/server.cpp
        src/client.cpp
        src/http.cpp
        src/router.cpp)
