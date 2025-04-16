/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsururukakou <tsururukakou@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:19:44 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/17 01:09:31 by tsururukako      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_xyz(t_xyz *xyz)
{
	xyz->x = 0.0;
	xyz->y = 0.0;
	xyz->z = 0.0;
}

void	init_env(t_env *env, t_lit *lit, int part)
{
	env->part = part;
	env->flag[A] = 0;
	env->flag[C] = 0;
	env->flag[L] = 0;
	env->amb_t = 0;
	init_xyz(&env->amb_rgb);
	init_xyz(&env->cam_xyz);
	init_xyz(&env->cam_vector);
	env->cam_degree = 0.0;
	env->lit = lit;
}

void	init_lit(t_lit *lit)
{
	lit->flag = 0;
	init_xyz(&lit->xyz);
	lit->t = 0;
	init_xyz(&lit->rgb);
	lit->valid_flag = true;
	lit->next = NULL;
}

void	init_obj(t_obj *data)
{
	data->id = -1;
	init_xyz(&data->xyz);
	init_xyz(&data->vector);
	init_xyz(&data->rgb);
	data->diameter = 0.0;
	data->height = 0.0;
	data->next = NULL;
}
