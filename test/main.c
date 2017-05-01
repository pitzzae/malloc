#include "../includes/malloc.h"
/* Pour les constantes EXIT_SUCCESS et EXIT_FAILURE */
#include <stdlib.h>
/* Pour fprintf() */
#include <stdio.h>
/* Pour fork() */
#include <unistd.h>
/* Pour perror() et errno */
#include <errno.h>
/* Pour le type pid_t */
#include <sys/types.h>

typedef struct		s_ptr
{
	char			*string1;
	char			*string2;
	char			*string3;
	struct s_ptr	*next;
}					t_ptr;

void use_ram(void)
{
	t_ptr	*ptr;
	t_ptr	*ptr_tmp;

	ptr = malloc(sizeof(t_ptr));
	ptr->string1 = malloc(sizeof(char) * 10000);
	ptr->string1[0] = '\0';
	ptr->string2 = malloc(sizeof(char) * 10000);
	ptr->string2[0] = '\0';
	ptr->string3 = malloc(sizeof(char) * 10000);
	ptr->string3[0] = '\0';
	ptr_tmp = ptr;
	while ((ptr->next = malloc(sizeof(t_ptr))))
	{
		ptr->string1 = malloc(sizeof(char) * 10000);
		ptr->string1[0] = '\0';
		ptr->string2 = malloc(sizeof(char) * 10000);
		ptr->string2[0] = '\0';
		ptr->string3 = malloc(sizeof(char) * 10000);
		ptr->string3[0] = '\0';
		ptr = ptr->next;
	}
	while (ptr_tmp->next)
	{
		ptr = ptr_tmp->next;
		free(ptr_tmp->string1);
		free(ptr_tmp->string2);
		free(ptr_tmp->string3);
		free(ptr_tmp);
		ptr_tmp = ptr;
	}
}


int		main(void)
{
	pid_t pid[3];

	(void)pid[0];
	pid[0] = fork();
	pid[1] = fork();
	use_ram();
	use_ram();
	use_ram();
}
