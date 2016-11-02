#include "../includes/malloc.h"
#include <stdio.h>

int		main(void)
{
	char		*ptr;

	(void)ptr;
	printf("coucou\n");
	ptr = malloc(99999);
	ptr[0] = 'a';
	ptr[1] = 'a';
	ptr[2] = 'a';
	ptr[3] = 'a';
	printf("%s\n", ptr);
	free(ptr);
	//printf("%s\n", ptr);
}
