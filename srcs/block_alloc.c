/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:04:34 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/30 03:15:14 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	init_page(to_return, page_len - PAGE_SIZE, size);
	add_page(to_return);
	return (to_return);
}

static t_block	*block_insert(t_page *p, size_t size)
{
	t_block	*b;

	b = (t_block*)PDATA(p);
	init_block(b, size);
	if (p->type != LARGE)
		split_block(b, page_size(p->size) - BLOCK_SIZE);
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
