#ifndef RAYTRACING_H
# define RAYTRACING_H

#include "./parser.h"
# define SHINENESS 16
# define NO_HIT -99
# define MAX_DIST 65535
# define EPSILON (1.0f/128)
# define RENDERED_SHADOW 0
# define NOT_RENDERED_SHADOW 1
# define NO_LIGHT 2

typedef enum e_letter {
	L_A,
	L_B,
	L_C,
	L_D
}	t_letter;


typedef struct s_ray
{
	t_xyz	pos;
	t_xyz	dir;
}	t_ray;
// dist is distance, pos is hit position, norm is nomral vector
typedef struct s_hit_point
{
	double	dist;
	t_xyz	pos;
	t_xyz	norm;
	int		index;
}	t_hit_point;

int		ray_tracing(t_obj *obj, t_env *env, t_ray cam_ray, t_xyz *color);
t_xyz	pls_shade(t_obj *obj, t_lit *lit, double diff_ref, double spec_ref);

double	convert_x_to_screen(int x);
double	convert_y_to_screen(int y);
void	set_screen_vector(t_xyz *screen, int x, int y, double fov);

double	hit_sphere(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit);
double	hit_plane(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit);
double	hit_cylinder(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit);
double	hit_cam_ray(t_obj *obj, t_ray *ray, t_hit_point *h_obj, bool rec_hit);

double	distance_sphere(double *abcd);
double	dist_cylndr(double *abcd, t_obj *obj, t_ray *ray, t_hit_point *h_obj);
double	hit_cylinder_caps(t_obj *obj, t_ray *ray, t_xyz norm_c);
double	get_nearest_inter_cy(t_obj *obj, t_xyz *h_pos, double *t, t_xyz norm_c);

void	fill_hit_obj(t_obj *obj, t_ray c_ray, t_hit_point *h_obj);
void	set_hit_obj(t_obj *obj, t_ray *ray, t_hit_point *h_obj, double dist);
void	set_h_obj_cy(t_obj *obj, t_ray *ray, t_hit_point *h_obj, double *t);
#endif