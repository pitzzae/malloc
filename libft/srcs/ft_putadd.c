/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:11:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/29 15:11:42 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putbase(unsigned long n, int base)
{
	char		c;

	if (n / base > 0)
	{
		ft_putbase((n / base), base);
		n = n % base;
	}
	c = n < 10 ? '0' : 'a' - 10;
	ft_putchar(c + n);
}


void			ft_putadd(void const *p)
{
	ft_putstr("0x");
	ft_putbase((unsigned long)p, 16);
}