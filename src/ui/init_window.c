#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/ui.h"

/* 一部calc 関数より抜出中、後日マージ後、置き換える*/
t_xyz   divid_v_f(t_xyz v, double f)
{
    t_xyz   tmp;

    // f = 0の場合の処理
    tmp.x = v.x / f;
    tmp.y = v.y / f;
    tmp.z = v.z / f;
    return (tmp);
}



double  sqr(double x)
{
    return (x * x);
}



double  calc_length2(t_xyz vector)
{
    return (sqr(vector.x) + sqr(vector.y) + sqr(vector.z));
}

double  calc_length(t_xyz vector)
{
    return (sqrt(calc_length2(vector)));
}

t_xyz   normalize(t_xyz vector)
{
    double  length;

    length = calc_length(vector);
    return (divid_v_f(vector, length));
}

t_xyz   minus_v1_v2(t_xyz v1, t_xyz v2)
{
    t_xyz   tmp;

    tmp.x = v1.x - v2.x;
    tmp.y = v1.y - v2.y;
    tmp.z = v1.z - v2.z;
    return (tmp);
}
/* ------------------------------------------- */

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
	//mlx_hook(mlx.window, DESTROY_NOTIFY, 0, close_btn_click, &mlx);
	mlx_loop(mlx.mlx);
	mlx_hook(mlx.window, DESTROY_NOTIFY, 0, close_btn_click, &mlx);
	return (EXIT_SUCCESS);
}

int	render_window(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	if (!mlx || !obj || !env)
		print_error_and_exit("render_window", "arg is NULL");
	mlx->img->img = mlx_new_image(mlx->mlx, W_WIDTH, W_HEIGHT);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, mlx->img->bits_per_pixel, \
	mlx->img->line_length, mlx->img->endian);
	render_scene(mlx, obj, env);
}

int	render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	rey_tracing();
}

double	convert_x_to_screen(int x)
{
	double	ret;

	ret = 2 * x;
	ret = ret / (W_WIDTH - 1) - 1;
	return (ret);
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
// この例では球に対しての判定
	camera_to_obj = minus_v1_v2(obj->vector, env->cam_xyz);
	a = squared_norm(&cam_dir);
	b = 2 * dot(&cam_dir, &camera_to_obj);
	c = squared_norm(&camera_to_obj) - sphere_r * sphere_r;
	return ()
	D = B * B - 4 * A * C;
}

int	ray_tracing(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	int				x;
	int				y;
	t_xyz	screen_vec;
	t_xyz	dir_vec;

	x = -1;
	y = -1;
	while (++y < W_WIDTH)
	{
		while (++x < W_HEIGHT)
		{
			// pixel から、ベクトルへの変換
			set_screen_vector(&screen_vec, x, y);
			// 方向ベクトル
			dir_vec = normalize(minus_v1_v2(screen_vec, env->cam_xyz));
			if (hit_ray() >= 0)

			else 
				
		}
	}
}

