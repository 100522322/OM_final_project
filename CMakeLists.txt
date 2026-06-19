cmake_minimum_required(VERSION 3.20)
project(OM_final_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(OM_final_project
        main.cpp
        Node.cpp
        Node.h
        Graph.cpp
        Graph.h
        SA.cpp
        SA.h
        ABC.cpp
        ABC.h
        DHS.cpp
        DHS.h
)

add_executable(tune
        tune.cpp
        Node.cpp
        Graph.cpp
        ABC.cpp
        DHS.cpp
)
