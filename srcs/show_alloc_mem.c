/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:34:04 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/30 22:10:07 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

static void show_block(t_block *b, int *len, size_t block_size)
{
	while(b != NULL)
	{
		if (b->is_free == 0 || b->is_free == 1)
		{
			ft_putadd(BDATA(b) - block_size);
			ft_putstr(" - ");
			ft_putadd(BDATA(b) + b->size - block_size);
			ft_putstr(" : ");
			ft_putnbr(b->size);
			if (b->is_free == 1)
				ft_putstr(" free");
			ft_putendl(" octets");
			len[0] += b->size;
		}
		b = b->next;
	}
}

static void show_page(t_page *p, int *len, size_t block_size)
{
	ft_putstr(page_name(p->type));
	ft_putstr(" : ");
	ft_putadd(p);
	ft_putstr("\n");
    show_block(p->first, len, block_size);
	if (p->next != NULL)
	{
		p = p->next;
		show_page(p, len, block_size);
	}
}


static void	show_alloc(size_t block_size)
{
	t_page	*p;
	int 	len;

	len = 0;
	p = first_page();
	if (p != NULL)
		show_page(p, &len, block_size);
	ft_putstr("Total : ");
	ft_putnbr(len);
	ft_putendl(" octets");
}

void        show_alloc_mem(void)
{
	show_alloc(0);
}

void        show_alloc_block(void)
{
	show_alloc(BLOCK_SIZE);
}
