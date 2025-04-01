/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsururukakou <tsururukakou@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:25:42 by yotsurud          #+#    #+#             */
/*   Updated: 2025/03/30 03:17:00 by tsururukako      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

t_vars	initialization(void)
{
	t_vars	env;

	env.zoom = 0.25;
	env.offset_x = 0.0;
	env.offset_y = 0.0;
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "fract-ol");
	env.img.img = mlx_new_image(env.mlx, WIDTH, HEIGHT);
	env.img.addr = mlx_get_data_addr(env.img.img, &env.img.bits_per_pixel,
			&env.img.line_length, &env.img.endian);
	return (env);
}

void	close_window(t_vars *env)
{
	mlx_destroy_window(env->mlx, env->win);
	exit(0);
}
