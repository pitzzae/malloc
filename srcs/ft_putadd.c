/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 15:11:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/23 16:51:59 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		ft_putbuf(char *buf)
{
	ft_putstr(buf);
	ft_bzero(buf, 48);
	ft_putstr("\n\t\t");
}

static void		ft_putbase(unsigned long n, char *buf, int base)
{
	char		c;

	if (n / base > 0)
	{
		ft_putbase((n / base), buf, base);
		n = n % base;
	}
	c = (char)(n < 10 ? '0' : 'a' - 10);
	c = (char)(c + n);
	ft_strcat_chr(buf, c);
}

void			print_hex(const char *s, const size_t len)
{
	char		buf[48];
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	ft_bzero(buf, 48);
	while (i < len)
	{
		if (((unsigned long)s[i] & 0x00F0) == 0)
			buf[j++] = '0';
		ft_putbase((unsigned long)s[i++] & 0x00FF, &buf[j++], 16);
		if (((unsigned long)s[i - 1] & 0x00F0) != 0)
			j++;
		if (i % 16 == 0)
		{
			ft_putbuf(buf);
			j = 0;
		}
		else
			buf[j++] = ' ';
	}
	if (buf[0])
		ft_putbuf(buf);
	ft_putstr("\n");
}

void			print_hex_string(const char *s, const size_t len)
{
	char		buf[48];
	size_t		i;

	i = 0;
	ft_bzero(buf, 48);
	while (i < len)
	{
		if ((s[i] & 0x00FF) >= 32 && (s[i] & 0x00FF) <= 126)
			ft_strcat_chr(buf, (const char)(s[i] & 0x00FF));
		else
			ft_strcat_chr(buf, '.');
		i++;
		if (i % 16 == 0)
			ft_putbuf(buf);
		else
		{
			ft_strcat_chr(buf, ' ');
			ft_strcat_chr(buf, ' ');
		}
	}
	if (buf[0])
		ft_putbuf(buf);
	ft_putchar('\n');
}

void			ft_putadd(void const *p)
{
	char		buf[32];

	ft_bzero(buf, 32);
	buf[0] = '0';
	buf[1] = 'x';
	ft_putbase((unsigned long)p, buf, 16);
	if (ft_strlen(buf) > 3)
		ft_putstr(buf);
	ft_bzero(buf, 32);
}
