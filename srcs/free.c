/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:22:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/01 18:56:21 by gtorresa         ###   ########.fr       */
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

void			check_page(t_block *b)
{
	t_page	*page;

	page = block_parent_page(b);
	if (page != NULL && page->first != NULL && page->first->is_free &&
			page->first->next == NULL)
		del_page(page);
}

void			free(void *ptr)
{
	t_block	*b;

	if (ptr == NULL)
		return ;
	b = search_ptr(ptr);
	b->is_free = 1;
	check_page(b);
}
