/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 15:53:16 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/01 18:53:46 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"
#include <stdio.h>

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
	show_alloc_mem();
	ft_strcpy( p, "Hello There!" );
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
	ft_strcpy( p, "This is a Test");
	p = (void *)ft_strchr( p, 's' );
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
	atexit(dump_garbage);
	for ( i = 0; i < 10; i++ )
		memarray[i] = (void *)ft_strdup( "string" );

	for ( i = 0; i < 10; i++ )
		memarray[i] = (void *)ft_strdup( "string" );

	for ( i = 0; i < 10; i++ )
		memarray[i] = malloc( 45 );

	for ( i = 0; i < 10; i++ )
		memarray[i] = calloc( 55, 1 );

	for ( i = 0; i < 10; i++ )
		memarray[i] = calloc( 55, 1 );

	for ( i = 0; i < 10; i++ )
	{
		show_alloc_mem();
		memarray[i] = realloc(memarray[i], 75 );
		show_alloc_mem();
	}
}

void
malloc_free_cycle( void )
{
	char *memarray[10];
	int i;

	for ( i = 0; i < 10; i++ )
		memarray[i] = ft_strdup( "string" );
	for ( i = 0; i < 10; i++ )
		free( memarray[i] );

	for ( i = 0; i < 10; i++ )
		memarray[i] = ft_strdup( "string" );
	for ( i = 0; i < 10; i++ )
		free( memarray[i] );

	for ( i = 0; i < 10; i++ )
	{
		memarray[i] = ft_strdup( "stringstringstringstring");
	}
	for ( i = 0; i < 10; i++ )
		free( memarray[i] );

	for ( i = 0; i < 10; i++ )
	{
		memarray[i] = ft_strdup( "stringstringstringstring");
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
	string2 = ft_strdup(string1);
	ft_putendl(string2);
	string2 = realloc(string2, 50);
	while (lenght < 500)
	{
		//show_alloc_mem();
		string2 = ft_strjoin_free(string2, string1, 1);
		ft_putendl(string2);
		lenght++;
		//show_alloc_mem();
		malloc_free_cycle();
	}
	ft_putendl("");
	if (fre == 1)
	{
		free(string1);
		free(string2);
	}
	ft_putendl("all free");
}

void
underrun()
{
	char *p;
#ifdef MALLOC_DEBUG
	mallopt(MALLOC_FILLAREA, 1);
#endif
	p = (char *)(void *)ft_strdup( "hello" );
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
		exit( 0 );
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
		default:;
	}
	return 0;
}
