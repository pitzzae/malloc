/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:28:41 by gtorresa          #+#    #+#             */
/*   Updated: 2015/12/02 14:29:17 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(long int n)
{
	long int	i;

	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
	}
	i = n - (n % 10);
	if (i > 0)
		ft_putnbr(i / 10);
	i = (n % 10) + 48;
	write(1, &i, 1);
}
