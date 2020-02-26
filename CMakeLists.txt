cmake_minimum_required(VERSION 3.14)
project(push_swap C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(libft)

add_executable(push_swap
#        push_swap.c
        new_and_free.c
        check_smthng.c
        set_index.c
        operations.c
        checker.c
        push_swap.h)

target_link_libraries(push_swap /Users/fboggs/Desktop/push_swap/printf/libftprintf.a)