/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:06:12 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/06 21:07:22 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_strcat_chr(char *dst, const char c)
{
	size_t	j;

	j = 0;
	while (dst[j] != '\0')
		j++;
    dst[j++] = c;
    dst[j] = '\0';
	return (dst);
}
