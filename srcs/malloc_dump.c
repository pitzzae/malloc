/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 23:11:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/06 23:51:09 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void     ft_print_output(t_block *b)
{
	if (b->is_free == 0)
	{
		ft_putadd(BDATA(b));
		ft_putstr(" - ");
		ft_putadd(BDATA(b) + b->size);
		ft_putstr(" : ");
		ft_putnbr(b->size);
		ft_putendl(" octets");
	}
	if (b->is_free == 1)
	{
		ft_putadd(BDATA(b));
		ft_putstr(" - ");
		ft_putadd(BDATA(b) + b->size);
		ft_putstr(" : ");
		ft_putnbr(b->size);
		ft_putendl(" free octets");
	}
}

static void		show_block(t_block *b, size_t debug)
{
	if (b != NULL)
	{
		ft_print_output(b);
		if (debug != 0 && b->next)
		{
			if (MALLOC_DEBUG == 2 || MALLOC_DEBUG >= 4)
			{
				ft_putstr("Dump_hexa:\t");
				print_hex((char*)BDATA(b), b->size);
			}
			if (MALLOC_DEBUG == 3 || MALLOC_DEBUG >= 4)
			{
				ft_putstr("Dump_str:\t");
				print_hex_string((char*)BDATA(b), b->size);
			}
		}
	}
}

void    inspect_alloc(void *ptr)
{
	t_block     *b;

	b = ptr - (BLOCK_SIZE + 1);
	ft_putendl("------------------------BLOCK_INSPECT"
		"--------------------------");
	show_block(b, 1);
	if (b->size > SMALL_ALLOC)
		ft_putendl("Couldn't display large block !!!");
	if (MALLOC_DEBUG == 5)
	{
		ft_putendl("-----------------------------------------------------------"
			"----");
		show_alloc(1);
	}
}

void    malloc_dump(char *msg, void *ptr, size_t len)
{
	ft_putstr(msg);
	ft_putstr(" ");
	ft_putadd(ptr);
	ft_putstr(" ");
	ft_putnbr(len);
	ft_putendl("");	
	inspect_alloc(ptr);
}
