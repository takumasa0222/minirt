/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shade.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:09:51 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 20:40:43 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include <math.h>
#include "../../includes/calc.h"

//this function calculate shade.
//shade including diffuse reflection and specular reflection
t_xyz	calc_shade(t_obj *obj, t_lit *lit, t_hit_point hit_obj, t_ray cam_ray)
{
	double	dot_res;
	t_xyz	reverse_vec;
	t_xyz	rev_cam_vec;
	double	specular_ref;
	t_xyz	incident_dir;

	specular_ref = 0.0;
	incident_dir = minus_v1_v2(lit->xyz, hit_obj.pos);
	incident_dir = normalize(incident_dir);
	dot_res = fmax(dot(incident_dir, hit_obj.norm), 0.0);
	if (dot_res > 0)
	{
		reverse_vec = minus_v1_v2(\
			multi_v_f(hit_obj.norm, 2 * dot_res), incident_dir);
		reverse_vec = normalize(reverse_vec);
		rev_cam_vec = multi_v_f(cam_ray.dir, -1);
		rev_cam_vec = normalize(rev_cam_vec);
		specular_ref = dot(reverse_vec, rev_cam_vec);
		specular_ref = pow(clamp_double(specular_ref, 0.0, 1.0), SHINENESS);
	}
	return (pls_shade(obj, lit, dot_res, specular_ref));
}
