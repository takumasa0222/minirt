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

void	free_lit(t_lit *lit)
{
	t_lit	*tmp;

	if (lit)
	{
		while (lit)
		{
			tmp = lit->next;
			free(lit);
			lit = tmp;
		}
	}
}

void	free_obj(t_obj *obj)
{
	t_obj	*tmp;

	if (obj)
	{
		while (obj)
		{
			tmp = obj->next;
			free(obj);
			obj = tmp;
		}
	}
}
