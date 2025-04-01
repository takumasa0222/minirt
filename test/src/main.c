/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsururukakou <tsururukakou@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:57:12 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/01 16:57:44 by tsururukako      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	color_set_to_pixel(t_data *data, int x, int y, unsigned int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	set_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	key_handler(int keycode, t_vars *env)
{
	if (keycode == ON_ESC)
		close_window(env);
	return (0);
}

int	render_next_frame(void *params)
{
	t_vars	*env;
	int		t = 0;
	int		r = 0;
	int		g = 0;
	int		b = 0;

	env = (t_vars *)params;
	t_cal_vars	m;
	m.y = 0;
	while (m.y < 800)
	{
		m.x = 0;
		while (m.x < 800)
		{
			r = ((799 - m.x) / 799) * 255;
			g = (m.y / 799) * 255 ;
			b = ((m.x * m.y) / (799 * 799)) * 255;
			color_set_to_pixel(&(*env).img, m.x, m.y, set_trgb(t, r, g, b));	
			m.x++;
		}
		m.y++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}

int	main()
{
	t_vars	env;

	env = initialization();	
	mlx_key_hook(env.win, key_handler, &env);
	mlx_loop_hook(env.mlx, render_next_frame, &env); // ←描画部分
	mlx_hook(env.win, ON_DESTROY, 0, (int (*)())close_window, &env);
	mlx_loop(env.mlx);
	return (0);
}
