#include "parser.h"

void    print_error_and_exit(char *func_name, char *message)
{
    ft_printf(2, "Error: %s: %s\n", func_name, message);
    exit(EXIT_FAILURE);
}

void    print_env_data(void)
{
    t_env   *env;

    env = set_get_env(GET, NULL);
    printf("flag[A] = %d\n", env->flag[A]);
    printf("flag[C] = %d\n", env->flag[C]);
    printf("flag[L] = %d\n", env->flag[L]);
    printf("amb_trgb = %X\n", env->amb_trgb);
    printf("cam_xyz.x = %0.1f\n", env->cam_xyz.x);
    printf("cam_xyz.y = %0.1f\n", env->cam_xyz.y);
    printf("cam_xyz.z = %0.1f\n", env->cam_xyz.z);
    printf("cam_vector.x = %0.1f\n", env->cam_vector.x);
    printf("cam_vector.y = %0.1f\n", env->cam_vector.y);
    printf("cam_vector.z = %0.1f\n", env->cam_vector.z);
    printf("cam_degree = %0.1f\n", env->cam_degree);
    printf("light_xyz.x = %0.1f\n", env->light_xyz.x);
    printf("light_xyz.y = %0.1f\n", env->light_xyz.y);
    printf("light_xyz.z = %0.1f\n", env->light_xyz.z);
    printf("light_trgb = %X\n", env->light_trgb);
}

void    print_obj_data(void)
{
    t_data  *data;

    data = set_get_data(GET, NULL);
    while (data)
    {
        printf("\n** print_obj_data **\n");
        printf("id = %d\n", data->id);
        printf("xyz.x = %0.1f\n", data->xyz.x);
        printf("xyz.y = %0.1f\n", data->xyz.y);
        printf("xyz.z = %0.1f\n", data->xyz.z);
        printf("vector.x = %0.1f\n", data->vector.x);
        printf("vector.y = %0.1f\n", data->vector.y);
        printf("vector.z = %0.1f\n", data->vector.z);
        printf("rgb = %X\n", data->rgb);
        printf("diamater = %0.2f\n", data->diameter);
        printf("height = %0.2f\n", data->height);

        data = data->next;
    }
}
