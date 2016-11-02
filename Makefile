#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 10:25:23 by gtorresa          #+#    #+#              #
#*   Updated: 2016/11/02 10:48:14 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= libft_malloc_$(HOSTTYPE).so

LIB_DIR		= ./libft
LIB_NAME	= $(LIB_DIR)/libft.a


CFLAGS		= -Wall -Wextra -Werror -fPIC
DLFLAGS		= -shared

SRCS_DIR	= srcs
OBJS_DIR	= objs
INCL_DIR	= includes

SRCS		= main.c

OBJECTS		= $(patsubst %.c, $(OBJS_DIR)/%.o, $(SRCS))

.PHONY: all

all: ${NAME}

$(NAME): $(OBJECTS)
	@make -C $(LIB_DIR)
	@echo "Make $(NAME)"
	@gcc $(DLFLAGS) -o $@ $(OBJECTS) -I./includes -L$(LIB_DIR) -lft

$(OBJS_DIR)/%.o: $(addprefix $(SRCS_DIR)/,%.c)
	@mkdir -p $(OBJS_DIR)
	$(CC) -c -o $@ $(CFLAGS) $^ -O0 -g  -I $(INCL_DIR)/

fclean: clean
	@rm -f $(NAME)
	@echo "Delete $(NAME)"

clean:
	@make -C $(LIB_DIR) fclean
	@rm -f $(LIB_NAME)
	@rm -rf $(OBJS_DIR)
	@echo "Delete $(LIB_NAME)"

re: fclean all
