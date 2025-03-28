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
    printf("part = %d\n", env->part);
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
}

void    print_lit_data(void)
{
    t_lit   *lit;

    lit = set_get_lit(GET, NULL);
    while (lit)
    {
        printf("\n** print_lit_data **\n");
        printf("lit->flag = %d\n", lit->flag);
        printf("lti->xyz.x = %0.1f\n", lit->xyz.x);
        printf("lit->xyz.y = %0.1f\n", lit->xyz.y);
        printf("lit->xyz.z = %0.1f\n", lit->xyz.z);
        printf("lit->trgb = %X\n", lit->trgb);
        lit = lit->next;
    }
}

void    print_obj_data(void)
{
    t_obj  *obj;

    obj = set_get_obj(GET, NULL);
    while (obj)
    {
        printf("\n** print_obj_data **\n");
        printf("id = %d\n", obj->id);
        printf("xyz.x = %0.1f\n", obj->xyz.x);
        printf("xyz.y = %0.1f\n", obj->xyz.y);
        printf("xyz.z = %0.1f\n", obj->xyz.z);
        printf("vector.x = %0.1f\n", obj->vector.x);
        printf("vector.y = %0.1f\n", obj->vector.y);
        printf("vector.z = %0.1f\n", obj->vector.z);
        printf("rgb = %X\n", obj->rgb);
        printf("diamater = %0.2f\n", obj->diameter);
        printf("height = %0.2f\n", obj->height);

        obj = obj->next;
    }
}
