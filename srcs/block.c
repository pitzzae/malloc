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

t_page		*block_parent_page(t_block *b)
{
	t_page	*iter;

	if (b == NULL)
		return (NULL);
	iter = first_page();
	while ((void*)iter < (void*)b)
	{
		if ((void*)iter < (void*)b && PDATA(iter) + iter->size > (void*)b)
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}