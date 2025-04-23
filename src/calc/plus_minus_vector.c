/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus_minus_vector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 05:29:12 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/12 16:34:57 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_xyz	plus_v1_v2(t_xyz v1, t_xyz v2)
{
	t_xyz	tmp;

	tmp.x = v1.x + v2.x;
	tmp.y = v1.y + v2.y;
	tmp.z = v1.z + v2.z;
	return (tmp);
}

t_xyz	minus_v1_v2(t_xyz v1, t_xyz v2)
{
	t_xyz	tmp;

	tmp.x = v1.x - v2.x;
	tmp.y = v1.y - v2.y;
	tmp.z = v1.z - v2.z;
	return (tmp);
}
