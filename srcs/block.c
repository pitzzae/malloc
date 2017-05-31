/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/31 17:49:38 by gtorresa         ###   ########.fr       */
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

void		check_last_block_size(t_page *p, t_block *b)
{
	if (b != NULL && b->next == NULL && p != NULL)
		b->size = (((long int)p + (long int)p->size - (long int)BDATA(b)) /
				sizeof(char)) - PAGE_SIZE;
}

static void	remove_free_block(t_page *p)
{
	t_block	*b;
	t_block	*tmp;
	size_t	size;

	b = p->first;
	while (b != NULL)
	{
		if (b->next != NULL && b->is_free == 1 && b->next->is_free == 1)
		{
			tmp = BDATA(b) - BLOCK_SIZE;
			size = b->size + b->next->size;
			b = b->next;
			init_block(tmp, size);
			tmp->next = b->next;
			tmp->is_free = 1;
		}
		if (b->next == NULL)
			check_last_block_size(p, b);
		b = b->next;
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
