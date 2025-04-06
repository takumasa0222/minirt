#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/ui.h"
#include "../../includes/calc.h"
#include <mlx.h>
#include <math.h>

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

void	set_screen_vector(t_xyz *screen, int x, int y, double fov)
{
	double	scale;

	scale = tan((fov * 0.5) * M_PI / 180.0);
	screen->x = convert_x_to_screen(x) * scale;
	screen->y = convert_y_to_screen(y) * scale;
	screen->z = 1;
}

double	distance_sphere(double *abcd)
{
	double	t[3];

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
	}
	return (t[0]);
}

// check if cam_ray is hitting to sphere and return distance
double	hit_sphere(t_obj *obj, t_env *env, t_xyz cam_dir)
{
	t_xyz	camera_to_obj;
	double	abcd[4];
	double	radius;

	radius = obj->diameter / 2.0;
	camera_to_obj = minus_v1_v2(env->cam_xyz, obj->vector);
	abcd[L_A] = squared_norm(&cam_dir);
	abcd[L_B] = 2 * dot(cam_dir, camera_to_obj);
	abcd[L_C] = squared_norm(&camera_to_obj) - radius * radius;
	abcd[L_D] = abcd[L_B] * abcd[L_B] - 4 * abcd[L_A] * abcd[L_C];
	if (abcd[L_D] <= 0)
		return (NO_HIT);
	return (distance_sphere(abcd));
}

double	hit_cam_ray(t_obj *obj, t_env *env, t_xyz cam_dir)
{
	if (obj->id == SP)
		return (hit_sphere(obj, env, cam_dir));
	//else if (obj->id == PL)
	//	hit_plane(obj, env, cam_dir, hit_p);
	//else if (obj->id == CY)
	//	hit_cylindar();
	return (NO_HIT);
}
// this funciton will return the index of object which is nearest
// -1 means there is no object which camera ray hit
int	hit_nearest_obj(t_obj *obj, t_env *env, t_ray *cam_ray, double *dist)
{
	t_obj	*obj_cpy;
	double	tmp;
	int		i;
	int		ret;

	*dist = MAX_DIST + 1;
	ret = -1;
	i = 0;
	obj_cpy = obj;
	while (obj_cpy)
	{
		tmp = hit_cam_ray(obj_cpy, env, cam_ray->dir);
		if (tmp > 0 && tmp < MAX_DIST && tmp < *dist)
		{
			*dist = tmp;
			ret = i;
		}
		obj_cpy = obj_cpy->next;
		i++;
	}
	return (ret);
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
		return (max);
	else
		return (value);
}

double	clamp_double(double value, double min, double max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}

void	clamp_xyz(t_xyz *rgb, double min, double max)
{
	rgb->x = clamp(rgb->x, min, max);
	rgb->y = clamp(rgb->y, min, max);
	rgb->z = clamp(rgb->z, min, max);
}

t_xyz	pls_shade(t_obj *obj, t_lit *lit, double diff_ref, double spec_ref)
{
	t_xyz	dif_col;
	t_xyz	spec_col;
	t_xyz	ret_col;
	t_xyz	lit_rgb;

	lit_rgb = lit->rgb;
	lit_rgb = divid_v_f(lit_rgb, 255.0);
	dif_col = multi_v_f(multi_v1_v2(obj->rgb, lit_rgb), diff_ref);
	dif_col = multi_v_f(dif_col, lit->t);
	spec_col = multi_v_f(multi_v_f(lit_rgb, 255.0), spec_ref);
	spec_col = multi_v_f(spec_col, lit->t);
	ret_col = plus_v1_v2(dif_col, spec_col);
	return (ret_col);
}

void	pls_amb_color(t_obj *obj, t_env *env, t_xyz *col)
{
	col->x = obj->rgb.x * env->amb_rgb.x / 255.0 * env->amb_t;
	col->y = obj->rgb.y * env->amb_rgb.y / 255.0 * env->amb_t;
	col->z = obj->rgb.z * env->amb_rgb.z / 255.0 * env->amb_t;
}


int	render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	int		x;
	int		y;
	t_xyz	color;
	t_xyz	screen_vec;
	t_ray	cam_ray;
	t_xyz screen_point;

	y = -1;
	init_xyz(&color);
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{	
			set_screen_vector(&screen_vec, x, y, env->cam_degree);
			screen_point = plus_v1_v2(env->cam_xyz, (t_xyz){screen_vec.x, screen_vec.y, screen_vec.z});
			cam_ray.pos = env->cam_xyz;
			cam_ray.dir = normalize(minus_v1_v2(screen_point, env->cam_xyz));
			if (ray_tracing(obj, env, cam_ray, &color))
				color_set_to_pixel(mlx->img, x, y, make_trgb(0, color.x, color.y, color.z));
			else
				color_set_to_pixel(mlx->img, x, y, rgb_to_int(100,149,237));
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img->img, 0, 0);
	return (EXIT_SUCCESS);
}

//this function calculate shade.
//shade including diffuse reflection and specular reflection
t_xyz	calc_shade(t_obj *obj, t_lit *lit, t_hit_point hit_obj, t_ray cam_ray)
{
	double		dot_res;
	t_xyz 		reverse_vec;// 正反射ベクトル
	t_xyz 		rev_cam_vec;// 視線の反対ベクトル
	double		specular_ref;//鏡面反射光
	t_xyz		incident_dir;//光の入射ベクトル

	specular_ref = 0.0;
	// diffuse light の実装
	// 正規化した入射ベクトル(交点から、光の位置)
	incident_dir = minus_v1_v2(lit->xyz, hit_obj.pos);
	incident_dir = normalize(incident_dir);
	// 法線ベクトルと入射ベクトルの内積(拡散反射光の輝度)
	dot_res = fmax(dot(incident_dir, hit_obj.norm), 0.0);
	//鏡面反射光の計算
	// 正反射ベクトル
	if (dot_res > 0)
	{
		reverse_vec = minus_v1_v2(multi_v_f(hit_obj.norm, 2 * dot_res), incident_dir);
		reverse_vec = normalize(reverse_vec);
		rev_cam_vec = multi_v_f(cam_ray.dir, -1);
		rev_cam_vec = normalize(rev_cam_vec);
		//鏡面反射光の輝度の計算
		specular_ref = dot(reverse_vec, rev_cam_vec);
		specular_ref = pow(clamp_double(specular_ref, 0.0, 1.0), SHINENESS);
	}
	return (pls_shade(obj, lit, dot_res, specular_ref));
}

t_obj	get_indexed_obj(int index, t_obj *obj)
{
	t_obj	*ret;
	int		j;

	ret = obj;
	if (!obj)
		print_error_and_exit("get_indexed_obj", "obj is null");
	if (index < 0)
		return (*obj);
	j = -1;
	while (ret && ++j != index)
		ret = ret->next;
	return (*ret);
}

void	fill_hit_obj(t_obj *obj, t_env *env, t_ray cam_ray, t_hit_point *hit_obj)
{
	// 平面・球における交点
	hit_obj->pos =  plus_v1_v2(env->cam_xyz, multi_v_f(cam_ray.dir, hit_obj->dist));
	// 正規化した法線ベクトル(球の中心から、交点)
	hit_obj->norm = minus_v1_v2(hit_obj->pos, obj->vector);
	hit_obj->norm = normalize(hit_obj->norm);
}

int	ray_tracing(t_obj *obj, t_env *env, t_ray cam_ray, t_xyz *color)
{
	t_hit_point	hit_obj;//交点情報を格納
	int			i;
	t_lit		*tmp_lit;
	t_obj		cpy_obj;

	i = hit_nearest_obj(obj, env, &cam_ray, &hit_obj.dist);
	cpy_obj = get_indexed_obj(i, obj);
	fill_hit_obj(&cpy_obj, env, cam_ray, &hit_obj);
	tmp_lit = env->lit;
	if (i >= 0)
	{
		pls_amb_color(&cpy_obj, env, color);
		while (tmp_lit)
		{
			*color = plus_v1_v2(calc_shade(&cpy_obj, tmp_lit, hit_obj, cam_ray), *color);
			tmp_lit = tmp_lit->next;
		}
		clamp_xyz(color, 0, 255);
		return (1);
	}
	return (0);
}

