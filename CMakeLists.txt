cmake_minimum_required(VERSION 3.20)
project(Epidemiological_modeling C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")

include_directories(.)

add_executable(Epidemiological_modeling
        main.c
        sirmodel.c
        checkparameter.c)
