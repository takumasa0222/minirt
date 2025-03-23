/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsururukakou <tsururukakou@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:54:06 by yotsurud          #+#    #+#             */
/*   Updated: 2025/03/23 16:56:46 by tsururukako      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int	ft_count_i(char const *s, char *str)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && ft_strchr(str, *s))
			s++;
		if (*s)
			count++;
		while (*s && !ft_strchr(str, *s))
			s++;
	}
	return (count);
}

static char	*ft_make_string_i(char const *s, char *str)
{
	size_t	j;
	size_t	len;
	char	*tmp;

	len = 0;
	while (s[len] && !ft_strchr(str, s[len]))
		len++;
	tmp = (char *)safe_malloc(len + 1, sizeof(char));
	j = -1;
	while (++j < len)
		tmp[j] = s[j];
	tmp[j] = '\0';
	return (tmp);
}

static void	*free_split(char **result, int i)
{
	if (result)
	{
		while (result[i])
			free(result[i--]);	
	}
	if (result)
		free(result);
	return (NULL);
}

char	**ft_split(char const *s, char *str)
{
	int		i;
	char	**result;
	
	if (!s || !str)
		print_error_and_exit("split function couldn't receive string");
	result = (char **)safe_malloc(ft_count_i(s, str) + 1, sizeof(char *));
	i = 0;
	while (*s)
	{
		while (*s && ft_strchr(str, *s))
			s++;
		if (*s && !ft_strchr(str, *s))
		{
			result[i] = ft_make_string_i(s, str);
			i++;
			while (*s && !ft_strchr(str, *s))
				s++;
		}
	}
	return (result);
}
