/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:11:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/30 03:15:32 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	split_block(t_block *b, size_t mem_width)
{
	t_block	*nb;

	if (b->size + BLOCK_SIZE == mem_width)
		return ;
	if (mem_width < b->size + BLOCK_SIZE * 2)
	{
		b->size = mem_width - BLOCK_SIZE * 2;
		return ;
	}
	nb = (t_block*)(BDATA(b) + b->size - 1);
	init_block(nb, mem_width - BLOCK_SIZE * 2 - b->size);
	nb->next = b->next;
	b->next = nb;
	nb->prev = b;
	nb->is_free = 1;
}

t_block *search_freed_block_in_page(t_page *p, size_t size)
{
	t_block		*b;

	b = p->first;
	while (b != NULL && !(b->is_free && b->size >= size))
		b = b->next;
	return (b);
}

t_block *search_freed_block(size_t size)
{
	t_page		*p;
	t_block		*b;
	size_t		mem_width;
	t_mtype		type;

	type = page_type(size);
	p = first_page();
	b = NULL;
	while (p != NULL)
	{
		if (p->type == type)
			b = search_freed_block_in_page(p, size);
		if (b != NULL)
			break ;
		p = p->next;
	}
	if (b == NULL)
		return (NULL);
	mem_width = b->size + BLOCK_SIZE;
	b->size = size;
	split_block(b, mem_width);
	b->is_free = 0;
	return (b);
}

void	*malloc_b(size_t size)
{
	t_block *b;

	b = search_freed_block(size);
	if (b == NULL)
		b = block_alloc(size);
	if (b == NULL)
		return (NULL);
	return (b);
}

void	*malloc(size_t size)
{
	t_block	*b;

	b = malloc_b(size);
	get_block_len(b, size);
	return (BDATA(b));
}
