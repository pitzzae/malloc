/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 16:55:36 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/06 23:51:39 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void        malloc_free_cycle(void)
{
    char *memarray[10];
    int i;

    for ( i = 0; i < 10; i++ )
        memarray[i] = strdup( "string" );
    for ( i = 0; i < 10; i++ )
        free( memarray[i] );

    for ( i = 0; i < 10; i++ )
        memarray[i] = strdup( "string" );
    for ( i = 0; i < 10; i++ )
        free( memarray[i] );

    for ( i = 0; i < 10; i++ )
    {
        memarray[i] = strdup( "stringstringstringstring");
    }
    for ( i = 0; i < 10; i++ )
        free( memarray[i] );

    for ( i = 0; i < 10; i++ )
    {
        memarray[i] = strdup( "stringstringstringstring");
    }
    for ( i = 0; i < 10; i++ )
        free( memarray[i] );

    for ( i = 0; i < 10; i++ )
        memarray[i] =  strdup( "string1string1string2string4string5string6");
    for ( i = 0; i < 10; i++ )
        memarray[i] = realloc( memarray[i], 10 );
    for ( i = 0; i < 10; i++ )
        memarray[i] = realloc( memarray[i], 75 );
    for ( i = 0; i < 10; i++ )
        free( memarray[i] );
}

char        *ft_strjoin(const char *s1, const char *s2)
{
		char*str;

	str = malloc(strlen(s1) + strlen(s2) + 1);
	if (	str == NULL)
		return (NULL);
	strcpy(str, s1);
	strcat(str, s2);
	return (str);
}

char        *ft_strjoin_free(char *s1, char *s2, int fre)
{
	char*str;

		str = malloc(strlen(s1) + strlen(s2) + 1);
		if (str == NULL)
			return (NULL);
		strcpy(str, s1);
		strcat(str, s2);
		str[strlen(s1) + strlen(s2)] = '\0';
		if (fre == 1)
			free(s1);
		if (fre == 2)
			free(s2);
		if (fre == 3)
		{
			free(s1);
			free(s2);
		}
	return (str);
}

void	    test_malloc(char *string1, char *string2)
{
	int		lenght;

	lenght = 0;
	string2 = "12345";
	string1 = ft_strjoin(string2, " 67890");
	string2 = strdup(string1);
	string2 = realloc(string2, 50);
	while (lenght < 500)
	{
		//show_alloc_mem();
		string2 = ft_strjoin_free(string2, string1, 1);
		lenght++;
        malloc_free_cycle();
		printf("%d/500\n", lenght);
		//show_alloc_mem();
	}
	free(string1);
	free(string2);
}

int		    main(void)
{
	char	*s;
	char	*s2;
    test_malloc(s, s2);
    test_malloc(s, s2);
    test_malloc(s, s2);
    malloc_free_cycle();
}
