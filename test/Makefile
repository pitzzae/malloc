#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 10:25:23 by gtorresa          #+#    #+#              #
#*   Updated: 2017/05/30 00:06:11 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

LIBFT_MALLOC	= `pwd`/../libft_malloc.so

NAME		= test_lib

CFLAGS		= -Wall -Wextra -Werror

SRCS		= main.c

.PHONY: all

all: ${NAME}

$(NAME):
	make -j 8 -C ../
	@echo "Make $(NAME)"
	#@gcc $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT_MALLOC) -I./../includes -L./../libft -lft
	@gcc $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFT_MALLOC) -I./../includes -L./../libft -lft
fclean: clean
	@rm -f $(NAME)
	@echo "Delete $(NAME)"

clean:
	@make -C ../ fclean
	@echo "Delete LIB_NAME"

re: fclean all
