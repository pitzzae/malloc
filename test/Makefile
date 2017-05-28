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

CFLAGS		= -Wall -Wextra -Werror -Wunused-function

SRCS		= main2.c

.PHONY: all

all: ${NAME}

$(NAME):
	make -j 8 -C ../
	@echo "Make $(NAME)"
	#@gcc $(CFLAGS) -o $(NAME) $(SRCS) `pwd`/../libft_malloc.so -I./../includes -L./../libft -lft
	@gcc $(CFLAGS) -o $(NAME) $(SRCS) `pwd`/../libft_malloc.so -I./../includes -L./../libft -lft
fclean: clean
	@rm -f $(NAME)
	@echo "Delete $(NAME)"

clean:
	@make -C ../ fclean
	@echo "Delete LIB_NAME"

re: fclean all
