cmake_minimum_required(VERSION 3.26.4)
project(Proyecto-Progra-3)

set(CMAKE_CXX_STANDARD 17)

add_executable(src
        src/inverted_trie/inverted.cpp
        src/inverted_trie/nodo.cpp
        src/login/autenticacion.cpp
        src/login/cuenta.cpp
        src/login/gestor_cuentas.cpp
        src/gestor_archivos.cpp
        src/functions.cpp
        src/main.cpp
        src/pelicula.cpp
        src/streaming.cpp
)