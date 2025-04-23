/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:20:15 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 19:21:03 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raytracing.h"

unsigned int	clamp(double value, int min, int max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}

double	clamp_double(double value, double min, double max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}

void	clamp_xyz(t_xyz *rgb, double min, double max)
{
	rgb->x = clamp(rgb->x, min, max);
	rgb->y = clamp(rgb->y, min, max);
	rgb->z = clamp(rgb->z, min, max);
}
