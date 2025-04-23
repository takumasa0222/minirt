/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:31:53 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 02:42:19 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/calc.h"

void	fill_hit_obj(t_obj *obj, t_ray c_ray, t_hit_point *h_obj)
{
	h_obj->pos = plus_v1_v2(c_ray.pos, multi_v_f(c_ray.dir, h_obj->dist));
	if (obj->id == SP)
	{
		h_obj->norm = minus_v1_v2(h_obj->pos, obj->xyz);
		h_obj->norm = normalize(h_obj->norm);
	}
	else if (obj->id == PL)
		h_obj->norm = normalize(obj->vector);
	else if (obj->id == CY)
		set_h_obj_cy(obj, &c_ray, h_obj, &h_obj->dist);
}

void	set_hit_obj(t_obj *obj, t_ray *ray, t_hit_point *h_obj, double dist)
{
	h_obj->dist = dist;
	h_obj->pos = plus_v1_v2(ray->pos, multi_v_f(ray->dir, h_obj->dist));
	if (obj->id == SP)
	{
		h_obj->norm = minus_v1_v2(h_obj->pos, obj->xyz);
		h_obj->norm = normalize(h_obj->norm);
	}
	else if (obj->id == PL)
		h_obj->norm = normalize(obj->vector);
}

void	set_h_obj_cy(t_obj *obj, t_ray *ray, t_hit_point *h_obj, double *t)
{
	if (t[0] == NO_HIT)
		return ;
	h_obj->dist = t[0];
	h_obj->pos = plus_v1_v2(ray->pos, multi_v_f(ray->dir, h_obj->dist));
	t_xyz C = obj->xyz;
	t_xyz V = normalize(obj->vector);
	double s = dot(minus_v1_v2(h_obj->pos, C), V);

	if (s >= 0 && s <= obj->height)
	{
		// 側面
		t_xyz Q = plus_v1_v2(C, multi_v_f(V, s));
		h_obj->norm = normalize(minus_v1_v2(h_obj->pos, Q));
	}
	else if (s < 0)
	{
		// 下キャップ
		h_obj->norm = multi_v_f(V, -1);
	}
	else
	{
		// 上キャップ
		h_obj->norm = V;
	}
	// if (t[0] == t[1])
	// {
		
	// }
	// else if (t[0] == t[2])
	// {
		
	// }
	// else if (t[0] == t[3])
	// {
		
	// }
}
