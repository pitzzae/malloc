/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 23:11:01 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/06 15:50:56 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void    malloc_dump(char *msg, void *ptr, size_t len)
{
    ft_putstr(msg);
    ft_putstr(" ");
    ft_putadd(ptr);
    ft_putstr(" ");
    ft_putnbr(len);
    ft_putendl("");
    show_alloc(1);
}
