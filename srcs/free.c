/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:22:15 by gtorresa          #+#    #+#             */
/*   Updated: 2016/11/02 16:22:15 by gtorresa         ###   ########.fr       */
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

static t_block	*fusion_block(t_block *beg)
{
	t_block	*end;

	end = beg;
	while (beg->prev != NULL && beg->prev->is_free)
		beg = beg->prev;
	while (end->next != NULL && end->next->is_free)
		end = end->next;
	if (beg == end)
	{
		beg->is_free = 1;
		return (beg);
	}
	beg->size = BDATA(end) + end->size - BDATA(beg);
	beg->next = end->next;
	beg->is_free = 1;
	return (beg);
}

void			check_page(t_block *b)
{
	t_page	*page;
	t_block	*first;

	page = block_parent_page(b);
	first = page->first;
	if (first != NULL &&
			first->is_free &&
			first->next == NULL)
		del_page(page);
}

void			free(void *ptr)
{
	t_block	*b;

	if (ptr == NULL)
		return ;
	b = search_ptr(ptr);
	if (b == NULL)
		return ;
	b = fusion_block(b);
	check_page(b);
}
