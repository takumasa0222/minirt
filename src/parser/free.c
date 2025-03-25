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

void	free_data(t_data *data)
{
	if (data)
	{
		while (data)
		{
			free(data);
			data = data->next;
		}
	}
}
