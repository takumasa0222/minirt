/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:52:11 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/20 18:53:50 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

double	squared_norm(t_xyz v)
{
	return (sqr(v.x) + sqr(v.y) + sqr(v.z));
}

double	distance_between(t_xyz a, t_xyz b)
{
	t_xyz	diff;

	diff = minus_v1_v2(a, b);
	return (sqrt(squared_norm(diff)));
}
