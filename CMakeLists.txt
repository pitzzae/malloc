cmake_minimum_required(VERSION 3.7)
project(ft_malloc)

set(CMAKE_C_STANDARD 99)
include_directories(includes)
set(HEADER_FILES includes/malloc.h)
set(SOURCE_FILES srcs/block.c srcs/block_alloc.c srcs/free.c srcs/malloc.c
        srcs/page.c srcs/page_type.c srcs/show_alloc_mem.c srcs/realloc.c
        srcs/malloc_dump.c srcs/ft_atoi.c srcs/ft_bzero.c
        srcs/ft_isdigit.c srcs/ft_memcpy.c srcs/ft_putadd.c srcs/ft_putchar.c
        srcs/ft_putendl.c srcs/ft_putnbr.c srcs/ft_putstr.c srcs/ft_strlen.c
        srcs/pthread.c srcs/ft_strcat_chr.c)
add_library(ft_malloc SHARED ${SOURCE_FILES} ${HEADER_FILES})