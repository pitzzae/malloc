/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:11:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/05 23:52:54 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		split_block(t_block *b, size_t mem_width)
{
	t_block		*nb;
	t_block		**btmp;

	if (b->size == mem_width)
		return ;
	if ((int)(b->size - mem_width - BLOCK_SIZE * 2) > 0)
	{
		nb = BDATA(b) + mem_width + BLOCK_SIZE - 1;
		btmp = &b->next;
		nb->size = b->size - (size_t)mem_width - (size_t)BLOCK_SIZE * 2;
		if (btmp[0] == NULL || btmp[0]->is_free == 0)
			nb->next = btmp[0];
		else
			nb->next = btmp[0]->next;
		b->next = nb;
		b->size = mem_width;
		nb->prev = b;
		nb->is_free = 1;
	}
	if (mem_width < b->size)
		b->size = mem_width;
}

t_block			*search_freed_block_in_page(t_page *p, size_t size)
{
	t_block		*b;

	b = p->first;
	while (b != NULL && !(b->is_free && b->size >= size))
		b = b->next;
	return (b);
}

t_block			*search_freed_block(size_t size)
{
	t_page		*p;
	t_block		*b;
	t_mtype		type;

	type = page_type(size);
	p = first_page();
	b = NULL;
	while (p != NULL)
	{
		check_last_block_size(p, p->first);
		if (p->type == type)
			b = search_freed_block_in_page(p, size);
		if (b != NULL)
			break ;
		p = p->next;
	}
	if (b == NULL)
		return (NULL);
	split_block(b, size);
	b->is_free = 0;
	return (b);
}

void			*malloc_b(size_t size)
{
	t_block		*b;

	b = search_freed_block(size);
	if (b == NULL)
		b = block_alloc(size);
	if (b == NULL)
		return (NULL);
	return (b);
}

void			*malloc(size_t size)
{
	t_block		*b;
	t_page      *p;

	p = first_page();
	b = malloc_b(size);
    if (MALLOC_DEBUG)
        malloc_dump("malloc", BDATA(b), size);
	return (BDATA(b));
}
