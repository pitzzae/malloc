#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/05 19:57:07 by gtorresa          #+#    #+#              #
#*   Updated: 2017/06/06 01:02:58 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

CC 			= gcc
NAME		= test

SRCS_DIR	= srcs
BIN_DIR		= bin
INCL_DIR	= includes

SRCS		= test0.c test1.c test2.c test3.c test3+.c test4.c

OBJECTS		= $(patsubst %.c, $(BIN_DIR)/%, $(SRCS))

.PHONY: all

all: ${NAME}

$(NAME): $(OBJECTS)
	$(CC) -o $(BIN_DIR)/test5 $(SRCS_DIR)/test5.c -L.. -lft_malloc
	@echo "Build"

$(BIN_DIR)/%: $(addprefix $(SRCS_DIR)/,%.c)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^

fclean: clean
	@echo "Delete bin"
	@rm -rf $(BIN_DIR)

clean:
	@echo ""

re: fclean all
