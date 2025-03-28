#include "parser.h"

void    init_xyz(t_xyz *xyz)
{
    xyz->x = 0.0;
    xyz->y = 0.0;
    xyz->z = 0.0;
}

void    init_env(t_env *env)
{
    env->flag[A] = 0;
    env->flag[C] = 0;
    // env->flag[L] = 0;
    env->amb_trgb = 0;
    init_xyz(&env->cam_xyz);
    init_xyz(&env->cam_vector);
    env->cam_degree = 0.0;
    // init_xyz(&env->light_xyz);
    // env->light_trgb = 0;
}

void    init_lit(t_lit *lit)
{
    lit->flag = 0;
    init_xyz(&lit->xyz);
    lit->trgb = 0;
    lit->next = NULL;
}

void    init_obj(t_obj *data)
{
    data->id = -1;
    init_xyz(&data->xyz);
    init_xyz(&data->vector);
    data->rgb = 0;
    data->diameter = 0.0;
    data->height = 0.0;
    data->next = NULL;
}
