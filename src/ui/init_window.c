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

double	clamp_double(double value, double min, double max)
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

t_xyz	calc_color(t_obj *obj, t_env *env, double diff_ref, double spec_ref)
{
	t_xyz	dif_col;
	t_xyz	spec_col;
	t_xyz	amb_col;
	t_xyz	ret_col;
	t_xyz	lit_rgb;

	lit_rgb = env->lit->rgb;
	lit_rgb.x /= 255.0;
	lit_rgb.y /= 255.0;
	lit_rgb.z /= 255.0;
	dif_col.x = obj->rgb.x * lit_rgb.x *diff_ref * env->lit->t;
	dif_col.y = obj->rgb.y * lit_rgb.y *diff_ref * env->lit->t;
	dif_col.z = obj->rgb.z * lit_rgb.z *diff_ref * env->lit->t;
	spec_col.x = 255.0 * lit_rgb.x *spec_ref * env->lit->t;
	spec_col.y = 255.0 * lit_rgb.y *spec_ref * env->lit->t;
	spec_col.z = 255.0 * lit_rgb.z *spec_ref * env->lit->t;
	amb_col.x = obj->rgb.x * env->amb_rgb.x / 255.0 * env->amb_t;
	amb_col.y = obj->rgb.y * env->amb_rgb.y / 255.0 * env->amb_t;
	amb_col.z = obj->rgb.z * env->amb_rgb.z / 255.0 * env->amb_t;
	ret_col.x = clamp(amb_col.x + dif_col.x + spec_col.x, 0, 255);
	ret_col.y = clamp(amb_col.y + dif_col.y + spec_col.y, 0, 255);
	ret_col.z = clamp(amb_col.z + dif_col.z + spec_col.z, 0, 255);
	return (ret_col);
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
	t_xyz reverse_vec;// 正反射ベクトル
	t_xyz rev_cam_vec;// 視線の反対ベクトル
	double	specular_ref;//鏡面反射光
	

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{	
			dot_res = 0.0;
			specular_ref = 0.0;
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
				// 法線ベクトルと入射ベクトルの内積(拡散反射光の輝度)
				dot_res = dot(incident_dir, normal_dir);
				//環境光(ambient ligth)の輝度の計算　La = Ka(環境光反射係数)Ea(環境光の照度)
				//env->amb_t
				//鏡面反射光の計算
				// 正反射ベクトル
				if (dot_res > 0)
				{
					reverse_vec = minus_v1_v2(multi_v_f(normal_dir, 2 * dot_res), incident_dir);
					reverse_vec = normalize(reverse_vec);
					rev_cam_vec = multi_v_f(dir_vec, -1);
					rev_cam_vec = normalize(rev_cam_vec);
					//鏡面反射光の輝度の計算
					specular_ref = dot(reverse_vec, rev_cam_vec);
					specular_ref = pow(clamp_double(specular_ref, 0.0, 1.0), SHINENESS);
				}
				color = calc_color(obj, env, dot_res, specular_ref);
				color_set_to_pixel(mlx->img, x, y, make_trgb(0, color.x, color.y, color.z));
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

