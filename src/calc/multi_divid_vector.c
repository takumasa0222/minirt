/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_divid_vector.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 05:28:37 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/12 16:32:37 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

t_xyz	multi_v1_v2(t_xyz v1, t_xyz v2)
{
	t_xyz	tmp;

	tmp.x = v1.x * v2.x;
	tmp.y = v1.y * v2.y;
	tmp.z = v1.z * v2.z;
	return (tmp);
}

t_xyz	multi_v_f(t_xyz v, double f)
{
	t_xyz	tmp;

	tmp.x = v.x * f;
	tmp.y = v.y * f;
	tmp.z = v.z * f;
	return (tmp);
}

t_xyz	divid_v1_v2(t_xyz v1, t_xyz v2)
{
	t_xyz	tmp;

	tmp.x = v1.x / v2.x;
	tmp.y = v1.y / v2.y;
	tmp.z = v1.z / v2.z;
	return (tmp);
}

t_xyz	divid_v_f(t_xyz v, double f)
{
	t_xyz	tmp;

	tmp.x = v.x / f;
	tmp.y = v.y / f;
	tmp.z = v.z / f;
	return (tmp);
}
