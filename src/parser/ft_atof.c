/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 05:19:33 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/12 15:23:04 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

char	*atof_init(char *nptr, double *sign)
{
	while (is_space(*nptr))
		nptr++;
	if (*nptr == '-')
		*sign = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	return (nptr);
}

char	*calc_integer(double *integer, char *nptr)
{
	while (ft_isdigit(*nptr))
	{
		if (*integer > DBL_MAX / 10)
			exit((printf("Error: invalid number\n"), 1));
		*integer = *integer * 10 + *nptr++ - '0';
	}
	return (nptr);
}

char	*calc_decimal(double *decimal, char *nptr, double integer)
{
	long long	num;
	int			power;

	if (*(nptr - 1) == '.' && !*nptr)
		return (nptr);
	num = 0;
	power = 0;
	while (ft_isdigit(*nptr))
	{
		if (num > DBL_MAX / 10)
			break ;
		num = num * 10 + *nptr++ - '0';
		if (num > 0 && (integer + ((double)num / pow(10.0, power)) < DBL_MIN))
		{
			num = 0;
			break ;
		}
		power++;
	}
	*decimal = (double)num / pow(10.0, power);
	while (ft_isdigit(*nptr))
		nptr++;
	return (nptr);
}

double	ft_atof(char *nptr)
{
	double	integer;
	double	decimal;
	double	sign;

	sign = 1.0;
	integer = 0.0;
	decimal = 0.0;
	nptr = atof_init(nptr, &sign);
	nptr = calc_integer(&integer, nptr);
	if (*nptr == '.')
		nptr++;
	nptr = calc_decimal(&decimal, nptr, integer);
	if (*nptr)
		exit((printf("Error: invalid number\n"), 1));
	else
		return (sign * (integer + decimal));
}
