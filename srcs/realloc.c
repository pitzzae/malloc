/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 00:53:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/31 17:50:26 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

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

static void	*realloc_inc(void *ptr, t_block *b, size_t size)
{
	t_block	*next;
	size_t 	old_size;
	void	*tmp;

	if (b->next != NULL && b->next->is_free == 1 &&
			b->next->size > size - b->size)
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
		ptr = malloc(size);
		ft_memcpy(ptr, tmp, b->size + BLOCK_SIZE);
		free(tmp);
	}
	return (ptr);
}

static void	*realloc_dec(void *ptr, t_block *b, size_t size)
{
	t_block	*next;
	size_t 	old_size;

	if (b->next != NULL && b->next->is_free == 0)
	{
		next = b->next->next;
		b->next = b->next - (size - b->size);
		b->next->next = next;
		b->next->prev = b;
		b->next->size = (b->size - size);
		b->next->is_free = 1;
		b->size = size;
	}
	else if (b->next != NULL && b->next->is_free == 1)
	{
		old_size = b->next->size;
		next = b->next->next;
		b->next = b->next - (size - b->size);
		b->next->next = next;
		b->next->prev = b;
		b->next->size = old_size + (b->size - size);
		b->next->is_free = 1;
		b->size = size;
	}
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*b;

	b = search_ptr(ptr);
	if (b != NULL && size > b->size)
		return (realloc_inc(ptr, b, size));
	else if (b != NULL && size < b->size)
		return (realloc_dec(ptr, b, size));
	return (ptr);
}
