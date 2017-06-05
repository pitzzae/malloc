/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/05 20:40:21 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *ft_strjoin(const char *s1, const char *s2)
{
		char*str;

	str = malloc(strlen(s1) + strlen(s2) + 1);
	if (	str == NULL)
		return (NULL);
	strcpy(str, s1);
	strcat(str, s2);
	return (str);
}


char *ft_strjoin_free(char *s1, char *s2, int fre)
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

void	test_calloc(void)
{
	char *ptr;
	int i, j;

	i = 0;
	j = 10;
	ptr = calloc(j, sizeof(char));
	ptr[0] = 'a';
	//show_alloc_block();
	while (i < j)
	{
		ptr[i] = 'a' + i;
		i++;
	}
	i = 0;
	while (i < j)
	{
		printf("%c",ptr[i]);
		i++;
	}
	printf("\n");
	free(ptr);
}

void
duplicate_free( void )
{
	char *p = malloc( 10 );
	free( p );
	free( p );
}

void
overrun( void )
{
	int *foo, *f, i;
#ifdef MALLOC_DEBUG
	mallopt(MALLOC_FILLAREA, 1);
#endif
	foo = malloc( 10*4 );
	for ( f = foo, i = 12; i > 0; f++, i-- )
		*f = 89;
	free( foo );
}

void
free_uninitialized( void )
{
	char *p = (void *)40000;
	free( p );
}

void
free_then_use( void )
{
	char *p;
#ifdef MALLOC_DEBUG
	mallopt(MALLOC_CKACCESS, 1);
#endif
	p = malloc( 30 );
	free( p );
	//show_alloc_mem();
	strcpy( p, "Hello There!" );
	p = malloc( 30 );
	free( p );
}

void
free_array( void )
{
	char p[10], *c = (char *)&p;
	free( c );
}

void
free_midrange( void )
{
	char *p = malloc( 30 );
	strcpy( p, "This is a Test");
	p = (void *)strchr( p, 's' );
	free( p );
}

void
dump_garbage()
{
#ifdef MALLOC_DEBUG
	malloc_mark(0);
    malloc_dump_unreferenced(STDERR_FILENO, 0);
#endif
}

void
just_leak( void )
{
	char *memarray[10];
	int i;
	for ( i = 0; i < 10; i++ )
		memarray[i] = (void *)strdup( "string" );

	for ( i = 0; i < 10; i++ )
		memarray[i] = (void *)strdup( "string" );

	for ( i = 0; i < 10; i++ )
		memarray[i] = malloc( 45 );

	for ( i = 0; i < 10; i++ )
		memarray[i] = calloc( 55, 1 );

	for ( i = 0; i < 10; i++ )
		memarray[i] = calloc( 55, 1 );

	for ( i = 0; i < 10; i++ )
	{
		//show_alloc_mem();
		memarray[i] = realloc(memarray[i], 75 );
		//show_alloc_mem();
	}
}

void
malloc_free_cycle( void )
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
		memarray[i] = malloc( 55 );
	for ( i = 0; i < 10; i++ )
		memarray[i] = realloc( memarray[i], 10 );
	for ( i = 0; i < 10; i++ )
		memarray[i] = realloc( memarray[i], 75 );
	for ( i = 0; i < 10; i++ )
		free( memarray[i] );
}

void	test_malloc(char *string1, char *string2, int fre)
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
		printf("%d/500\n", lenght);
		//show_alloc_mem();
		malloc_free_cycle();
	}
	if (fre == 1)
	{
		free(string1);
		free(string2);
	}
}

void
underrun()
{
	char *p;
#ifdef MALLOC_DEBUG
	mallopt(MALLOC_FILLAREA, 1);
#endif
	p = (char *)(void *)strdup( "hello" );
	p -= 4;
	*p = 88;
	p += 4;
	free( p );
}

void
dohelp( void )
{
	printf( "\nUsage:\n\t1\tduplicate_free\n\t2\toverrun\n\t3\tfree_uninitialized\n\t4\tfree_then_use\n\t5\tfree_array\n\t6\tfree_midrange\n");
	printf( "\t7\tunderrun\n\t8\tnode corruption\n\t9\tjust_leak\n\t10\tmalloc/free cycling\n\n");
}

int
main( int argc, char **argv )
{
	char	*string1 = NULL;
	char	*string2 = NULL;
	if( argc < 2 ) {
		dohelp();
		return 0;
	}
	switch( atoi( argv[1] ) ) {
		case 1:
			duplicate_free();
			break;
		case 2:
			overrun();
			break;
		case 3:
			free_uninitialized();
			break;
		case 4:
			free_then_use();
			break;
		case 5:
			free_array();
			break;
		case 6:
			free_midrange();
			break;
		case 7:
			underrun();
			break;
		case 8:
			just_leak();
			break;
		case 9:
			test_malloc(string1, string2, 0);
			test_malloc(string1, string2, 1);
			test_malloc(string1, string2, 1);
			break;
		case 10:
			malloc_free_cycle();
			break;
		case 11:
			test_malloc(string1, string2, 0);
			test_malloc(string1, string2, 1);
			malloc_free_cycle();
			just_leak();
			test_calloc();
			break;
		case 12:
			test_calloc();
		default:;
	}
	return 0;
}
