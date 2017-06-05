/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:34:04 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/06 01:02:20 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void     ft_print_output(t_block *b, size_t debug)
{
    if (b->is_free == 0)
    {
        ft_putadd(BDATA(b));
        ft_putstr(" - ");
        ft_putadd(BDATA(b) + b->size);
        ft_putstr(" : ");
        ft_putnbr(b->size);
    }
    if (b->is_free == 1 && debug)
    {
        ft_putadd(BDATA(b));
        ft_putstr(" - ");
        ft_putadd(BDATA(b) + b->size);
        ft_putstr(" : ");
        ft_putnbr(b->size);
        ft_putstr(" free");
    }
    ft_putendl(" octets");
}

static void		show_block(t_block *b, int *len, size_t debug)
{
	while (b != NULL)
	{
		if (b->is_free == 0 || b->is_free == 1)
		{
            ft_print_output(b, debug);
			if (debug)
            {
                ft_putstr("\t");
                ft_putendl(BDATA(b));
            }
			len[0] += b->size;
		}
		b = b->next;
	}
}

static void		show_page(t_page *p, int *len, size_t debug)
{
	ft_putstr(page_name(p->type));
	ft_putstr(" : ");
	ft_putadd(p);
	ft_putstr("\n");
	show_block(p->first, len, debug);
	if (p->next != NULL)
	{
		p = p->next;
		show_page(p, len, debug);
	}
}

void		    show_alloc(size_t debug)
{
	t_page	*p;
	int		len;

	len = 0;
	p = first_page();
	if (p != NULL)
		show_page(p, &len, debug);
	ft_putstr("Total : ");
	ft_putnbr(len);
	ft_putendl(" octets");
}

void			show_alloc_mem(void)
{
    pthread_mutex_lock(get_mutex());
    show_alloc(0);
    pthread_mutex_unlock(get_mutex());
}
