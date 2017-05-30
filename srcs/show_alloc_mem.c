/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:11:42 by gtorresa          #+#    #+#             */
/*   Updated: 2016/11/02 15:11:42 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

static void show_block(t_block *b, int *len)
{
	while(b != NULL)
	{
		if (b->is_free == 0 || b->is_free == 1)
		{
			ft_putadd(b);
			ft_putstr(" - ");
			ft_putadd(b + b->size);
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

static void show_page(t_page *p, int *len)
{
	ft_putstr(page_name(p->type));
	ft_putstr(" : ");
	ft_putadd(p);
	ft_putstr("\n");
    show_block(p->first, len);
	if (p->next != NULL)
	{
		p = p->next;
		show_page(p, len);
	}
}

void        show_alloc_mem(void)
{
    t_page	*p;
	int 	len;

	len = 0;
    p = first_page();
	if (p != NULL)
    	show_page(p, &len);
	ft_putstr("Total : ");
	ft_putnbr(len);
	ft_putendl(" octets");
}