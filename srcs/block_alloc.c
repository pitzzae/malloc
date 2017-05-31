/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:04:34 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/31 17:49:43 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		split_block(t_block *b, size_t mem_width)
{
	t_block	*nb;

	if (b->size == mem_width)
		return ;
	if (mem_width < b->size + BLOCK_SIZE)
	{
		b->size = mem_width;
		return ;
	}
	nb = (t_block*)(BDATA(b) + b->size - 1);
	init_block(nb, mem_width - BLOCK_SIZE - PAGE_SIZE - b->size);
	nb->next = b->next;
	b->next = nb;
	nb->prev = b;
	nb->is_free = 1;
}

static t_page	*page_alloc(size_t size)
{
	t_page	*to_return;
	size_t	page_len;

	page_len = page_length(size);
	to_return = (t_page*)mmap(NULL,
			page_len,
			PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON,
			-1,
			0);
	init_page(to_return, page_len, size);
	add_page(to_return);
	return (to_return);
}

static t_block	*block_insert(t_page *p, size_t size)
{
	t_block	*b;

	b = (t_block*)PDATA(p);
	init_block(b, size);
	if (p->type != LARGE)
		split_block(b, page_size(p->size) - PAGE_SIZE);
	p->first = b;
	return (b);
}

t_block			*block_alloc(size_t size)
{
	t_page	*p;
	t_block	*b;

	p = page_alloc(size);
	b = block_insert(p, size);
	return (b);
}
