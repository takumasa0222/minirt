#ifndef RAYTRACING_H
# define RAYTRACING_H

# define SHINENESS 16
# define NO_HIT -99
# define MAX_DIST 65535
#include "./parser.h"

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
}	t_hit_point;

int	ray_tracing(t_obj *obj, t_env *env, t_ray cam_ray, t_xyz *color);
#endif