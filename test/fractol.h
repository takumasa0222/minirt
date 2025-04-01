/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsururukakou <tsururukakou@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:53:40 by yotsurud          #+#    #+#             */
/*   Updated: 2025/03/30 04:01:37 by tsururukako      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./minilibx_opengl/mlx.h"
// # include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define MAX_COUNT 200
# define WIDTH 800
# define HEIGHT 800
# define MOVE_STEP 100
# define TRUE 1
# define FALSE 0

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	char		*command1;
	double		zoom;
	double		offset_x;
	double		offset_y;
	t_data		img;
}			t_vars;

typedef struct s_cal_vars
{
	double	x;
	double	y;
	int		i;
	int		j;
	int		count;	
}				t_cal_vars;

enum {
	ON_KEYLEFT = 123,
	ON_KEYRIGHT = 124,
	ON_KEYUP = 126,
	ON_KEYDOWN = 125,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_DESTROY = 17,
	ON_ESC = 53
};

t_vars			initialization(void);
void			close_window(t_vars *env);
int				key_handler(int keycode, t_vars *env);
int				render_next_frame(void *params);
void			color_set_to_pixel(t_data *data, int x, int y,
					unsigned int color);
// int				mouse_handler(int mousecode, int x, int y, t_vars *env);

#endif
