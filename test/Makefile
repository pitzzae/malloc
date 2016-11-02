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

NAME		= test_lib

CFLAGS		= -Wall -Wextra -Werror

SRCS		= main.c

.PHONY: all

all: ${NAME}

$(NAME):
	@echo "Make $(NAME)"
	@gcc $(CFLAGS) -o $(NAME) $(SRCS) ../libft_malloc_x86_64_Linux.so

fclean: clean
	@rm -f $(NAME)
	@echo "Delete $(NAME)"

clean:
	@echo "Delete LIB_NAME"

re: fclean all
