/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 16:22:15 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/31 17:51:34 by gtorresa         ###   ########.fr       */
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

void			check_page(t_block *b)
{
	t_page	*page;
	t_page	*tmp;

	page = block_parent_page(b);
	if (page != NULL && page->first != NULL && page->first->is_free &&
			page->first->next == NULL)
	{
		del_page(page);
		tmp = first_page();
	}
}

void			free(void *ptr)
{
	t_block	*b;

	if (ptr == NULL)
		return ;
	ft_putadd(ptr);
	ft_putendl(" *ptr free before ------------");
	show_alloc_block();
	b = search_ptr(ptr);
	b->is_free = 1;
	ft_putendl("free after");
	show_alloc_block();
	ft_putendl("");
	if (b != NULL)
		check_page(b);
}
