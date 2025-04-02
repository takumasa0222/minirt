#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/ui.h"
#include "../../includes/calc.h"
#include <mlx.h>

double squared_norm(t_xyz *v)
{
  return sqr(v->x) + sqr(v->y) + sqr(v->z);
}

int	init_window(t_obj *data, t_env *env)
{
	t_mlx_env	mlx;

	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, W_WIDTH, W_HEIGHT, WIN_TITLE);
	render_window(&mlx, data, env);
	mlx_hook(mlx.window, DESTROY_NOTIFY, 0, close_btn_click, &mlx);
	mlx_loop(mlx.mlx);
	return (EXIT_SUCCESS);
}

int	render_window(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	if (!mlx || !obj || !env)
		print_error_and_exit("render_window", "arg is NULL");
	mlx->img = malloc(sizeof(t_meta_img));
	if (!mlx->img)
		print_error_and_exit("mlx_new_image failed", NULL);
	mlx->img->img = mlx_new_image(mlx->mlx, W_WIDTH, W_HEIGHT);
	if (!mlx->img->img)
		print_error_and_exit("mlx_new_image failed", NULL);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img->bits_per_pixel, \
	&mlx->img->line_length, &mlx->img->endian);
	if (!mlx->img->addr)
		print_error_and_exit("mlx_new_image failed", NULL);
	render_scene(mlx, obj, env);
	return (EXIT_SUCCESS);
}

int	render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	ray_tracing(mlx, obj, env);
	return (EXIT_SUCCESS);
}

double	convert_x_to_screen(int x)
{
	double	ret;
	double	aspect_ratio;

	aspect_ratio = (double)W_WIDTH / (double)W_HEIGHT;
	ret = 2 * x;
	ret = ret / (W_WIDTH - 1) - 1;
	return (ret * aspect_ratio);
}

double	convert_y_to_screen(int y)
{
	double	ret;

	ret = -2 * y;
	ret = ret / (W_HEIGHT - 1) + 1;
	return (ret);
}

void	set_screen_vector(t_xyz *screen, int x, int y)
{
	screen->x = convert_x_to_screen(x);
	screen->y = convert_y_to_screen(y);
}

double	hit_ray(t_obj *obj, t_env *env, t_xyz cam_dir)
{
	t_xyz	camera_to_obj;
	double	a;
	double	b;
	double	c;
	double	radius;

	radius = obj->diameter / 2.0;
// この例では球に対しての判定を行う
	camera_to_obj = minus_v1_v2(obj->vector, env->cam_xyz);
	a = squared_norm(&cam_dir);
	b = 2 * dot(cam_dir, camera_to_obj);
	c = squared_norm(&camera_to_obj) - radius * radius;
	//printf("a = %f\n", a);
	//printf("b = %f\n", b);
	//printf("c = %f\n", c);
	return (b * b - 4 * a * c);
}

unsigned int	set_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


void	color_set_to_pixel(t_meta_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int rgb_to_int(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}

int	ray_tracing(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	int				x;
	int				y;
	t_xyz	screen_vec;
	t_xyz	dir_vec;


	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			// pixel から、ベクトルへの変換
			set_screen_vector(&screen_vec, x, y);
			// 方向ベクトル
			dir_vec = normalize(minus_v1_v2(screen_vec, env->cam_xyz));
			if (hit_ray(obj, env, dir_vec) >= 0)
				color_set_to_pixel(mlx->img, x, y, obj->rgb);
			else
				color_set_to_pixel(mlx->img, x, y, rgb_to_int(0,255,255));

		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img->img, 0, 0);
	return (EXIT_SUCCESS);
}

