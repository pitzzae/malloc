/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:11:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/06 15:50:48 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		ft_isprint(int c1)
{
    if (c1 >= 32 && c1 <= 126)
        return (1);
    return (0);
}

static void		ft_putbase(unsigned long n, int base)
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

void            print_hex(const char *s, const size_t len)
{
    size_t      i;

    i = 0;
    while(i < len)
    {
        if (((unsigned long)s[i] & 0x00F0) == 0)
            ft_putchar('0');
        ft_putbase((unsigned long)s[i++] & 0x00FF, 16);
        if (i % 16 == 0 && i < len)
            ft_putstr("\n\t\t\t");
        else
            ft_putstr(" ");
    }
    ft_putstr("\n");
}

void            print_hex_string(const char *s, const size_t len)
{
    size_t      i;

    i = 0;
    while(i < len)
    {
        if (ft_isprint(s[i] & 0x00FF))
            ft_putchar(s[i] & 0x00FF);
        else
            ft_putchar('.');
        i++;
        if (i % 16 == 0 && i < len)
            ft_putstr("\n\t\t\t");
        else
            ft_putchar(' ');
    }
    ft_putchar('\n');
}

void			ft_putadd(void const *p)
{
	ft_putstr("0x");
	ft_putbase((unsigned long)p, 16);
}
