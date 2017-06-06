/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:11:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/06 21:06:19 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int		ft_isprint(int c1)
{
    if (c1 >= 32 && c1 <= 126)
        return (1);
    return (0);
}

static void		ft_putbase(unsigned long n, char *buf, int base)
{
	char		c;

	if (n / base > 0)
	{
		ft_putbase((n / base), buf, base);
		n = n % base;
	}
	c = n < 10 ? '0' : 'a' - 10;
    c = c + n;
    ft_strcat_chr(buf, c);
}

void            print_hex(const char *s, const size_t len)
{
    char        buf[48];
    size_t      i;
    size_t      j;

    i = 0;
    j = 0;
    ft_bzero(buf, 48);
    while(i < len)
    {
        if (((unsigned long)s[i] & 0x00F0) == 0)
        {
            buf[j++] = '0';
            ft_putbase((unsigned long)s[i++] & 0x00FF, &buf[j++], 16);
        }
        else
        {
            ft_putbase((unsigned long)s[i++] & 0x00FF, &buf[j++], 16);
            j++;
        }




        if (i % 16 == 0 && i < len)
        {
            ft_putstr(buf);
            ft_bzero(buf, 48);
            j = 0;
            ft_putstr("\n\t\t");
        }
        else
            buf[j++] = ' ';
    }
    ft_putstr("\n");
}

void            print_hex_string(const char *s, const size_t len)
{
    char        buf[48];
    size_t      i;
    size_t      j;

    i = 0;
    j = 0;
    ft_bzero(buf, 48);
    while(i < len)
    {
        if (ft_isprint(s[i] & 0x00FF))
            buf[j++] = (s[i] & 0x00FF);
        else
            buf[j++] = '.';
        i++;
        if (i % 16 == 0 && i < len)
        {
            ft_putstr(buf);
            ft_bzero(buf, 48);
            j = 0;
            ft_putstr("\n\t\t");
        }
        else
        {
            buf[j++] = ' ';
            buf[j++] = ' ';
        }
    }
    ft_putchar('\n');
}

void			ft_putadd(void const *p)
{
	char        buf[32];

    ft_bzero(buf, 32);
    buf[0] = '0';
    buf[1] = 'x';
	ft_putbase((unsigned long)p, buf, 16);
    ft_putstr(buf);
}
