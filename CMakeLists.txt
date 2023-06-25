cmake_minimum_required(VERSION 3.25)
project(test C)

set(CMAKE_C_STANDARD 17)


add_executable(test main.c stack/stack.c stack/stack.h pair/pair.c pair/pair.h utils.h minimumStack/minstack.h minimumStack/minstack.c utils.c)
