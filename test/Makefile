#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 10:25:23 by gtorresa          #+#    #+#              #
#*   Updated: 2017/06/06 01:02:29 by gtorresa         ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

LIBFT_MALLOC	= `pwd`/../libft_malloc.so

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

ifeq ($(HOSTTYPE), x86_64_Darwin)
	ADD_LINK = @ln -s $(LIBFT_MALLOC) ./libft_malloc_$(HOSTTYPE).so
	DEL_LINK = @rm -rf ./libft_malloc_$(HOSTTYPE).so
endif

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
	$(ADD_LINK)

fclean: clean
	@rm -f $(NAME)
	@echo "Delete $(NAME)"
	$(DEL_LINK)

clean:
	@make -C ../ fclean
	@echo "Delete libft_malloc_$(HOSTTYPE).so"

re: fclean all
