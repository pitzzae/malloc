#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 10:25:23 by gtorresa          #+#    #+#              #
#*   Updated: 2017/06/05 20:21:29 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

CC 			= gcc
NAME		= libft_malloc_$(HOSTTYPE).so

CFLAGS		= -Wall -Wextra -Werror
DLFLAGS		= -shared -fPIC

SRCS_DIR	= srcs
OBJS_DIR	= objs
INCL_DIR	= includes

SRCS		= malloc.c page.c page_type.c block.c block_alloc.c free.c \
			show_alloc_mem.c realloc.c calloc.c ft_bzero.c ft_memcpy.c \
			ft_putadd.c ft_putendl.c ft_putstr.c ft_atoi.c ft_putnbr.c \
			ft_putchar.c ft_strlen.c ft_isdigit.c

OBJECTS		= $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))

.PHONY: all

all: ${NAME}

$(NAME): $(OBJECTS)
	@gcc $(DLFLAGS) -o $@ $(OBJECTS)
	@rm -f libft_malloc.so
	@ln -s $(NAME) libft_malloc.so
	@echo libft_malloc.so now link to $(NAME)

$(OBJS_DIR)/%.o: $(addprefix $(SRCS_DIR)/,%.c)
	@mkdir -p $(OBJS_DIR)
	$(CC) -c -o $@ $(CFLAGS) $^ -O0 -g -I $(INCL_DIR)/

fclean: clean
	@rm -f $(NAME)
	@rm -f libft_malloc.so
	@echo "Delete objs"

clean:
	@rm -f $(OBJECTS)
	@rm -rf $(OBJS_DIR)

re: fclean all
