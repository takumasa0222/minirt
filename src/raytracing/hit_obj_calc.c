/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_obj_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 00:31:53 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 14:18:55 by tamatsuu         ###   ########.fr       */
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
	t_xyz	obj_center;
	t_xyz	obj_vector;
	t_xyz	pos;
	double	s;

	if (t[0] == NO_HIT)
		return ;
	h_obj->dist = t[0];
	h_obj->pos = plus_v1_v2(ray->pos, multi_v_f(ray->dir, h_obj->dist));
	obj_center = obj->xyz;
	obj_vector = normalize(obj->vector);
	s = dot(minus_v1_v2(h_obj->pos, obj_center), obj_vector);
	if (s >= 0 && s <= obj->height)
	{
		pos = plus_v1_v2(obj_center, multi_v_f(obj_vector, s));
		h_obj->norm = normalize(minus_v1_v2(h_obj->pos, pos));
	}
	else if (s < 0)
		h_obj->norm = multi_v_f(obj_vector, -1);
	else
		h_obj->norm = obj_vector;
}
