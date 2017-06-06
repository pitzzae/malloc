/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 00:53:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/06 17:43:01 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_block	*search_ptr_in_page(t_page *page, void *ptr)
{
	t_block		*iter;

	iter = page->first;
	while (iter != NULL)
	{
		if (ptr == BDATA(iter))
			return (iter);
		if (iter->is_free > 1)
		{
			iter->next = NULL;
			check_last_block_size(page, iter);
		}
		iter = iter->next;
	}
	return (NULL);
}

static t_block	*search_ptr(void *ptr)
{
	t_page		*page;
	t_block		*block;

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

static void		*realloc_inc(void *ptr, t_block *b, size_t size)
{
	t_block		*next;
	size_t		old_size;
	void		*tmp;

	if (b->next != NULL && b->next->is_free == 1 &&
			(b->next->size + b->size + BLOCK_SIZE) - size > 0)
	{
		old_size = b->next->size;
		next = b->next->next;
		b->next += size - b->size;
		b->next->next = next;
		b->next->prev = b;
		b->next->size = old_size - (size - b->size);
		b->next->is_free = 1;
		b->size = size;
	}
	else
	{
		tmp = ptr;
        pthread_mutex_unlock(get_mmutex());
		ptr = malloc(size);
		ft_bzero(ptr, size);
		ft_memcpy(ptr, tmp, b->size);
		free(tmp);
	}
	return (ptr);
}

static void		*realloc_dec(void *ptr, t_block *b, size_t size)
{
	t_block		*nb;

	if (b->next != NULL && b->next->is_free == 0 && b->size > size + BLOCK_SIZE)
	{
		nb = b;
		nb += (BLOCK_SIZE + size);
		nb->prev = b;
		nb->next = b->next;
		nb->size = b->size - (BLOCK_SIZE + size);
		nb->is_free = 1;
		b->next = nb;
	}
	else if (b->next != NULL && b->next->is_free == 1)
	{
		nb = b;
		nb += (BLOCK_SIZE + size);
		nb->prev = b;
		nb->next = b->next->next;
		nb->size = (b->size - (BLOCK_SIZE + size)) + BLOCK_SIZE + b->next->size;
		nb->is_free = 1;
		b->next = nb;
	}
	b->size = size;
    if (MALLOC_DEBUG)
        malloc_dump("realloc dec", BDATA(ptr), size);
	return (ptr);
}

void			*realloc(void *ptr, size_t size)
{
	t_block		*b;

    pthread_mutex_lock(get_mmutex());
	b = search_ptr(ptr);
	if (b != NULL && size > b->size)
		return (realloc_inc(ptr, b, size));
	else if (b != NULL && size < b->size)
		return (realloc_dec(ptr, b, size));
	if (b == NULL && ptr != NULL)
		return (NULL);
    pthread_mutex_unlock(get_mmutex());
    if (MALLOC_DEBUG)
        ft_putadd(ptr);
	ptr = malloc(size + 1);
    ft_bzero(ptr, size + 1);
    if (MALLOC_DEBUG)
        malloc_dump(" realloc NB", ptr, size);
	return (ptr);
}
