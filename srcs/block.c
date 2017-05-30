/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2016/11/02 15:53:16 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "malloc.h"

void		init_block(void *ptr, size_t s)
{
	t_block	*tb;

	if (ptr == NULL)
		return ;
	tb = (t_block*)ptr;
	tb->size = s;
	tb->next = NULL;
	tb->prev = NULL;
	tb->is_free = 0;
}

void		init_page(void *ptr, t_mtype size, size_t block_size)
{
	t_page	*page;

	page = (t_page*)ptr;
	page->type = page_type(block_size);
	page->size = size;
	page->prev = NULL;
	page->next = NULL;
	page->first = NULL;
}

static void	remove_free_block(t_page *p)
{
	t_block	*b;
	size_t	size;

	b = p->first;
	size = p->size;
	while (b->next != NULL)
		b = b->next;
	while (b->prev != NULL && b->is_free == 1)
	{
		size += b->size + BLOCK_SIZE;
		b = b->prev;
		b->next = NULL;

	}
}

t_page		*block_parent_page(t_block *b)
{
	t_page	*iter;

	if (b == NULL)
		return (NULL);
	iter = first_page();

	while (iter != NULL)
	{
		if (iter->first != NULL)
			remove_free_block(iter);
		if ((void*)iter < (void*)b && (void*)iter + iter->size +
									  BLOCK_SIZE > (void*)b)
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}