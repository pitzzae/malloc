/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/30 03:17:15 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "malloc.h"

void	test_malloc(char *string1, char *string2, int fre)
{
	int		lenght;

	lenght = 0;
	string1 = ft_strjoin("                    ", "                    ");
	string2 = ft_strjoin(string1, string1);
	string2 = realloc(string2, 10);
	show_alloc_mem();
	while (lenght < 2)
	{
		//ft_putstr("string1: ");
		//ft_putendl(string1);
		//ft_putstr("string2: ");
		//ft_putendl(string2);
		//ft_putnbr((ft_strlen(string1) + ft_strlen(string2)) * sizeof(char));
		string2 = ft_strjoin_free(string2, string1, 1);
		//ft_putstr("\nstring-join: ");
		//ft_putendl(string2);
		lenght++;
		//ft_putstr("\n>>end\n");

	}
	ft_putendl("");
	show_alloc_mem();
	//ft_putendl(string2);
	//ft_putnbr(ft_strlen(string2));
	if (fre == 1)
	{
		free(string1);
		free(string2);
	}
	ft_putendl("all free");
	show_alloc_mem();
}

int		main(void)
{
	char	*string1 = NULL;
	char	*string2 = NULL;
	test_malloc(string1, string2, 0);
	test_malloc(string1, string2, 1);
	test_malloc(string1, string2, 1);
}
