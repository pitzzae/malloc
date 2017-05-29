/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:22:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/30 00:10:44 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*search_ptr_in_page(t_page *page, void *ptr)
{
	t_block	*iter;

	iter = page->first;
	while (iter != NULL)
	{
		if (ptr == BDATA(iter))
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

static t_block	*search_ptr(void *ptr)
{
	t_page	*page;
	t_block	*block;

	page = first_page();
	while (page != NULL)
	{
		block = search_ptr_in_page(page, ptr);
		if (block != NULL)
			return (block);
		page = page->next;
	}
	return (NULL);
}

void		get_block_len(t_block *beg, size_t size)
{
	t_block	*end;
	int		size_free;
	int		nb;

	size_free = 0;
	nb = 0;
	end = beg;
	while (end->prev != NULL)
		end = end->prev;
	while (end->next != NULL)
	{
		size_free += end->size;
		nb++;
		end = end->next;
	}
	end->size = page_length(size) - (size_free + nb * BLOCK_SIZE) - PAGE_SIZE;
}

static t_block	*fusion_block(t_block *beg)
{
	t_block	*end;
	int		size_free;

	size_free = 0;
	end = beg;
	while (beg != NULL && beg->prev != NULL && beg->prev->is_free)
	{
		beg = beg->prev;
		size_free += beg->size + BLOCK_SIZE;
	}
	while (end->next != NULL && end->next->is_free)
	{
		end = end->next;
		size_free += end->size + BLOCK_SIZE;
	}
	if (beg == end)
	{
		beg->is_free = 1;
		return (beg);
	}
	beg->size = BDATA(end) + end->size - BDATA(beg);
	beg->size = size_free;
	beg->next = end->next;
	beg->is_free = 1;

	return (beg);
}

void			check_page(t_block *b)
{
	t_page	*page;

	page = block_parent_page(b);
	if (page != NULL && page->first != NULL && page->first->is_free && page->first->next == NULL)
		del_page(page);
}

void			free(void *ptr)
{
	t_block	*b;

	if (ptr == NULL)
		return ;
	b = search_ptr(ptr);
	get_block_len(b, b->size);
	if (b == NULL)
		return ;
	b = fusion_block(b);
	check_page(b);
}
