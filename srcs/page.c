/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:11:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/31 17:49:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

static t_page	**get_first_page(void)
{
	static t_page	*first = NULL;

	return (&first);
}

t_page			*first_page(void)
{
	return (*get_first_page());
}

void			free_all(void)
{
	t_page	*iter;
	t_page	*page;

	iter = first_page();
	while (iter != NULL)
	{
		page = iter;
		iter = iter->next;
		munmap(page, page->size + PAGE_SIZE);
	}
	*get_first_page() = NULL;
}

void			del_page(t_page *page)
{
	if (page->prev == NULL && page->next)
		*get_first_page() = NULL;
	if (page->prev != NULL)
		page->prev->next = page->next;
	else
		*get_first_page() = page->next;
	if (page->next != NULL)
		page->next->prev = page->prev;
	ft_putadd(page);
	ft_putendl(" munmap");
	show_alloc_block();
	ft_putendl("");
	munmap(page, page->size);
}

void			add_page(t_page *new_page)
{
	t_page	*last_page;

	if (first_page() == NULL)
		*get_first_page() = new_page;
	else
	{
		last_page = first_page();
		while (last_page->next != NULL)
			last_page = last_page->next;
		new_page->prev = last_page;
		last_page->next = new_page;
	}
}
