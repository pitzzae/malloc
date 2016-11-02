#include "../includes/malloc.h"
#include <stdio.h>

int		main(void)
{
	t_page		*ptr;

	(void)ptr;
	printf("coucou\n");
	printf("%d\n", getpagesize());
	ft_print_text();
}
