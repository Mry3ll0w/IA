cmake_minimum_required(VERSION 3.20)
project(Practicas_Adversario C)

set(CMAKE_C_STANDARD 99)

add_executable(Practicas_Adversario main.c tictactoe.h tictactoe.c minimaxAlum.h minimaxAlum.c)
