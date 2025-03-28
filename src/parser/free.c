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
	t_data	*tmp;

	if (data)
	{
		while (data)
		{
			tmp = data->next;
			free(data);
			data = tmp;
		}
	}
}
