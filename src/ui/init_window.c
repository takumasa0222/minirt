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
	double	abcd[4];
	double	radius;
	double	t[3];
	// double	t1;
	// double	t2;

	radius = obj->diameter / 2.0;
// この例では球に対しての判定を行う
	camera_to_obj = minus_v1_v2(env->cam_xyz, obj->vector);
	abcd[L_A] = squared_norm(&cam_dir);
	abcd[L_B] = 2 * dot(cam_dir, camera_to_obj);
	abcd[L_C] = squared_norm(&camera_to_obj) - radius * radius;
	abcd[L_D] = abcd[L_B] * abcd[L_B] - 4 * abcd[L_A] * abcd[L_C];
	// 媒介変数 t の計算
	t[0] = -1;
	if (abcd[L_D] == 0)
		t[0] = - abcd[L_B] / (2 * abcd[L_A]);
	else if (abcd[L_D] > 0)
	{
		t[1] = (- abcd[L_B] + sqrt(abcd[L_D])) / (2 * abcd[L_A]);
		t[2] = (- abcd[L_B] - sqrt(abcd[L_D])) / (2 * abcd[L_A]);
		if (t[1] > 0 && t[2] > 0)
			t[0] = fmin(t[1], t[2]);
		else if (t[1] > 0)
			t[0] = t[1];
		else if (t[2] > 0)
			t[0] = t[2];
		//printf("t: (%f, %f, %f)\n", t[0], t[1], t[2]);
		//printf("A: %f, B: %f, C: %f, D: %f\n", abcd[L_A], abcd[L_B], abcd[L_C], abcd[L_D]);
		//printf("cam_dir: (%f, %f, %f)\n", cam_dir.x, cam_dir.y, cam_dir.z);
		//printf("camera_to_obj: (%f, %f, %f)\n", camera_to_obj.x, camera_to_obj.y, camera_to_obj.z);
	}
	return (t[0]);
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

unsigned int	clamp(double value, int min, int max)
{
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else
		return value;
}

void	clamp_xyz(t_xyz *rgb, double dot_res)
{
	rgb->x = clamp(rgb->x * dot_res, 0, 255);
	rgb->y = clamp(rgb->y * dot_res, 0, 255);
	rgb->z = clamp(rgb->z * dot_res, 0, 255);
}

int	ray_tracing(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	int		x;
	int		y;
	t_xyz	screen_vec;
	t_xyz	dir_vec;
	t_xyz	incident_dir;//光の入射ベクトル
	t_xyz	normal_dir;//法線ベクトル
	t_xyz	cross_vec;//球との交点ベクトル
	double	t;
	double	dot_res;
	t_xyz color;
	
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
			t = hit_ray(obj, env, dir_vec);
			if (t > 0)
			{
				// diffuse light の実装
				// 正規化した入射ベクトル
				cross_vec =  plus_v1_v2(env->cam_xyz, multi_v_f(dir_vec, t));
				incident_dir = minus_v1_v2(env->lit->xyz, cross_vec);
				incident_dir = normalize(incident_dir);
				// 正規化した法線ベクトル
				normal_dir = minus_v1_v2(cross_vec, obj->vector);
				normal_dir = normalize(normal_dir);
				// 法線ベクトルと入射ベクトルの内積
				dot_res = dot(incident_dir, normal_dir);
				color = obj->rgb;
				clamp_xyz(&color, dot_res);
				//multi_v_f(obj->rgb, dot_res);
				if (dot_res > 0)
					printf("%f\n",dot_res);
				color_set_to_pixel(mlx->img, x, y, make_trgb(dot_res, color.x, color.y, color.z));
			}
			else
			{
				color_set_to_pixel(mlx->img, x, y, rgb_to_int(100,149,237));
			}
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img->img, 0, 0);
	return (EXIT_SUCCESS);
}

