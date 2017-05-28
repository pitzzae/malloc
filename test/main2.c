#include "../includes/malloc.h"
/* Pour les constantes EXIT_SUCCESS et EXIT_FAILURE */
#include <stdlib.h>
/* Pour fprintf() */


int		main(void)
{
	char	*string1;
	char	*string2;
	int		lenght;

	lenght = 0;
	string1 = ft_strjoin("coucou ", "cest moi\n");
	string2 = ft_strjoin("coucou ", "cest moi\n");
	while (lenght < 5000)
	{
		//printf("%zu\n", ft_strlen(string1) + ft_strlen(string2));
		//printf("%s\n\n%s", string1, string2);
		string1 = ft_strjoin_free(string1, string2, 1);
		lenght++;
	}
	//printf("%s\n", string1);
	//printf("%zu\n", ft_strlen(string1));
	free(string1);
	free(string2);
}
