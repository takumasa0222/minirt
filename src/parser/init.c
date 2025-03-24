#include "parser.h"

t_xyz    init_xyz(void)
{
    t_xyz   tmp;

    tmp.x = 0.0;
    tmp.y = 0.0;
    tmp.z = 0.0;
    return (tmp);
}

void    init_env(t_env *env)
{
    env->flag[A] = 0;
    env->flag[C] = 0;
    env->flag[L] = 0;
    env->amb_trgb = 0;
    env->cam_xyz = init_xyz();
    env->cam_vector = init_xyz();
    env->cam_degree = 0.0;
    env->light_xyz = init_xyz();
    env->light_trgb = 0;
}

void    init_data(t_data *data)
{
    data->id = -1;
    data->xyz = init_xyz();
    data->vector = init_xyz();
    data->rgb = 0;
    data->diameter = 0.0;
    data->height = 0.0;
    data->next = NULL;
}
