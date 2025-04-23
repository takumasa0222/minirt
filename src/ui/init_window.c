/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamatsuu <tamatsuu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:54:11 by tamatsuu          #+#    #+#             */
/*   Updated: 2025/04/23 02:28:12 by tamatsuu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/raytracing.h"
#include "../../includes/ui.h"
#include "../../includes/calc.h"
#include <mlx.h>
#include <math.h>

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
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, \
		&mlx->img->bits_per_pixel, &mlx->img->line_length, &mlx->img->endian);
	if (!mlx->img->addr)
		print_error_and_exit("mlx_new_image failed", NULL);
	render_scene(mlx, obj, env);
	return (EXIT_SUCCESS);
}

// this funciton will return the index of object which is nearest
// -1 means there is no object which camera ray hit
int	hit_nearest_obj(t_obj *obj, t_ray *ray, t_hit_point *hit_p)
{
	t_obj	*obj_cpy;
	double	tmp;
	int		i;
	int		ret;

	hit_p->dist = MAX_DIST + 1;
	ret = -1;
	i = 0;
	obj_cpy = obj;
	while (obj_cpy)
	{
		tmp = hit_cam_ray(obj_cpy, ray, hit_p, true);
		if (tmp > 0 && tmp < MAX_DIST && tmp < hit_p->dist)
		{
			hit_p->dist = tmp;
			ret = i;
		}
		obj_cpy = obj_cpy->next;
		i++;
	}
	if (hit_p->dist == MAX_DIST + 1)
		hit_p->dist = -1;
	return (ret);
}

int	hit_shadow_ray(t_obj *obj, t_ray *sh_ray, t_hit_point *hit_p)
{
	t_obj	*obj_cpy;
	double	tmp;
	int		i;
	int		ret;

	ret = -1;
	i = 0;
	obj_cpy = obj;
	while (obj_cpy)
	{		
		if (hit_p->index == i)
		{
			obj_cpy = obj_cpy->next;
			i++;
			continue ;
		}
		tmp = hit_cam_ray(obj_cpy, sh_ray, hit_p, false);
		if (tmp > EPSILON && tmp < MAX_DIST && tmp < hit_p->dist)
		{
			hit_p->dist = tmp;
			ret = i++;
		}
		obj_cpy = obj_cpy->next;
	}
	return (ret);
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

// todo : 複数光源に対応するため、env ではだめ
// need to fix: シャドウレイとの間にある物体の中で光源に最も近い物体が平面である場合、すべて環境光のみとなる: done
// todo 4/20: 物体に、影が当たるときは、ハードシャドウを完全な黒にするのではなく、物体に合わせた色にすべき: done
int	calc_shadow(t_obj *obj, t_lit *lit, t_hit_point *hit_p)
{
	t_ray		shadow_ray;
	t_xyz		incident_dir;
	double		dist_shadow_to_lit;
	double		ret;
	t_hit_point	tmp_hit;

	incident_dir = minus_v1_v2(lit->xyz, hit_p->pos);
	incident_dir = normalize(incident_dir);
	tmp_hit = *hit_p;
	shadow_ray.pos = plus_v1_v2(hit_p->pos, multi_v_f(incident_dir, EPSILON));
	shadow_ray.dir = incident_dir;
	dist_shadow_to_lit = distance_between(lit->xyz, hit_p->pos);
	ret = hit_shadow_ray(obj, &shadow_ray, &tmp_hit);
	if (ret != -1 && tmp_hit.dist > EPSILON \
		&& tmp_hit.dist < dist_shadow_to_lit - EPSILON)
		return (RENDERED_SHADOW);
	return (NOT_RENDERED_SHADOW);
}

void	color_set_to_pixel(t_meta_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	clamp(double value, int min, int max)
{
	if (value < min)
		return (min);
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
	col->x = obj->rgb.x * (env->amb_rgb.x / 255.0) * env->amb_t;
	col->y = obj->rgb.y * (env->amb_rgb.y / 255.0) * env->amb_t;
	col->z = obj->rgb.z * (env->amb_rgb.z / 255.0) * env->amb_t;
}

void	check_light_and_cam_pos(t_obj *obj, t_lit *lit, t_ray cam_ray)
{
	double	dot_n_light;
	double	dot_n_camera;
	t_xyz	norm_p;

	norm_p = normalize(obj->vector);
	dot_n_light = dot(norm_p, minus_v1_v2(lit->xyz, obj->xyz));
	dot_n_camera = dot(norm_p, minus_v1_v2(cam_ray.pos, obj->xyz));
	if ((dot_n_light > 0 && dot_n_camera > 0) \
	|| (dot_n_light < 0 && dot_n_camera < 0))
		lit->valid_flag = true;
	else
		lit->valid_flag = false;
}

void	check_light_pos(t_obj *obj, t_env *env, t_ray cam_ray)
{
	t_obj	*obj_cpy;
	t_lit	*lit_cpy;

	lit_cpy = env->lit;
	while (lit_cpy)
	{
		obj_cpy = obj;
		while (obj_cpy)
		{
			if (obj_cpy->id == PL)
				check_light_and_cam_pos(obj_cpy, lit_cpy, cam_ray);
			obj_cpy = obj_cpy->next;
		}
		lit_cpy = lit_cpy->next;
	}
}

t_xyz	calc_cam_dir(t_xyz screen_vec, t_xyz cam_vec)
{
	t_xyz	dir;
	t_xyz	forward;
	t_xyz	up;
	t_xyz	right;

	forward = normalize(cam_vec);
	up.x = 0;
	up.y = 1;
	up.z = 0;
	if (fabs(dot(forward, up)) > 0.999)
		up = (t_xyz){1, 0, 0};
	right = normalize(cross(up, forward));
	up = cross(forward, right);
	dir = normalize(\
		plus_v1_v2(\
			plus_v1_v2(\
				multi_v_f(right, screen_vec.x), multi_v_f(up, screen_vec.y)), \
				forward));
	return (dir);
}

int	render_scene(t_mlx_env *mlx, t_obj *obj, t_env *env)
{
	int		x;
	int		y;
	t_xyz	color;
	t_xyz	screen_vec;
	t_ray	cam_ray;

	y = -1;
	init_xyz(&color);
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
		{	
			set_screen_vector(&screen_vec, x, y, env->cam_degree);
			cam_ray.pos = env->cam_xyz;
			cam_ray.dir = calc_cam_dir(screen_vec, env->cam_vector);
			check_light_pos(obj, env, cam_ray);
			ray_tracing(obj, env, cam_ray, &color);
			color_set_to_pixel \
				(mlx->img, x, y, make_trgb(0, color.x, color.y, color.z));
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img->img);
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

int	set_amb_col(t_xyz *color, t_env *env)
{
	color->x = (env->amb_rgb.x / 255.0) * env->amb_t;
	color->y = (env->amb_rgb.y / 255.0) * env->amb_t;
	color->z = (env->amb_rgb.z / 255.0) * env->amb_t;
	return (0);
}

int	ray_tracing(t_obj *obj, t_env *env, t_ray cam_ray, t_xyz *color)
{
	t_hit_point	hit_obj;
	t_lit		*tmp_lit;
	t_obj		cpy_obj;
	int			ret;

	hit_obj.index = hit_nearest_obj(obj, &cam_ray, &hit_obj);
	if (hit_obj.index < 0)
		return (set_amb_col(color, env), 0);
	cpy_obj = get_indexed_obj(hit_obj.index, obj);
	fill_hit_obj(&cpy_obj, cam_ray, &hit_obj);
	tmp_lit = env->lit;
	if (hit_obj.index >= 0)
	{
		pls_amb_color(&cpy_obj, env, color);
		while (tmp_lit && tmp_lit->valid_flag)
		{
			ret = calc_shadow(obj, tmp_lit, &hit_obj);
			if (ret == NOT_RENDERED_SHADOW)
				*color = plus_v1_v2(\
					calc_shade(&cpy_obj, tmp_lit, hit_obj, cam_ray), *color);
			tmp_lit = tmp_lit->next;
		}
		return (clamp_xyz(color, 0, 255), 1);
	}
	return (0);
}
