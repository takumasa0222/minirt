#include "parser.h"

void	free_split(char **split)
{
    int i;

    i = -1;
	if (split)
	{
		while (split[++i])
			free(split[i]);	
	}
	if (split)
		free(split);
}
