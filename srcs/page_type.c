/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:11:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/31 21:27:42 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

char		*page_name(t_mtype type)
{
	if (type == TINY)
		return ("TINY");
	if (type == SMALL)
		return ("SMALL");
	return ("LARGE");
}

t_mtype		page_type(size_t size)
{
	if (size <= TINY_ALLOC)
		return (TINY);
	if (size <= SMALL_ALLOC)
		return (SMALL);
	return (LARGE);
}

size_t		page_length(size_t size)
{
	if (size <= TINY_ALLOC)
		return (size_t) (TINY_LENGTH);
	if (size <= SMALL_ALLOC)
		return (size_t) (SMALL_LENGTH);
	return (size + PAGE_SIZE + BLOCK_SIZE);
}

size_t		page_size(t_mtype size)
{
	if (size == TINY)
		return (size_t) (TINY_LENGTH);
	if (size == SMALL)
		return (size_t) (SMALL_LENGTH);
	return (size + PAGE_SIZE);
}
