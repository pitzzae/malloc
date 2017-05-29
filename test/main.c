/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 00:09:07 by gtorresa          #+#    #+#             */
/*   Updated: 2017/05/30 00:09:11 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

void	test_malloc(char *string1, char *string2, int fre)
{
	int		lenght;

	lenght = 0;
	string1 = ft_strjoin("coucou ", "cest moi\n");
	string2 = ft_strjoin("coucou ", "cest moi\n");
	while (lenght < 5000)
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
