cmake_minimum_required(VERSION 3.28)
project(src)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Login)

add_executable(src
        inverted_trie/inverted.cpp
        inverted_trie/nodo.cpp
        Login/credenciales.cpp
        #Login/credenciales.h
        #Login/cuentas.cpp
        functions.cpp
        #functions.h
        main.cpp
        pelicula.cpp
        streaming.cpp
)
