/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_light_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:24:54 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 19:25:27 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/calc.h"

void	check_light_and_cam_pos(t_obj *obj, t_lit *lit, t_ray cam_ray)
{
	double	dot_n_light;
	double	dot_n_camera;
	t_xyz	norm_p;

	norm_p = normalize(obj->vector);
	dot_n_light = dot(norm_p, minus_v1_v2(lit->xyz, obj->xyz));
	dot_n_camera = dot(norm_p, minus_v1_v2(cam_ray.pos, obj->xyz));
	if ((dot_n_light > 0 && dot_n_camera > 0) \
	|| (dot_n_light < 0 && dot_n_camera < 0))
		lit->valid_flag = true;
	else
		lit->valid_flag = false;
}

void	check_light_pos(t_obj *obj, t_env *env, t_ray cam_ray)
{
	t_obj	*obj_cpy;
	t_lit	*lit_cpy;

	lit_cpy = env->lit;
	while (lit_cpy)
	{
		obj_cpy = obj;
		while (obj_cpy)
		{
			if (obj_cpy->id == PL)
				check_light_and_cam_pos(obj_cpy, lit_cpy, cam_ray);
			obj_cpy = obj_cpy->next;
		}
		lit_cpy = lit_cpy->next;
	}
}
