#include "parser.h"


void    print_env_data()
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

void    parser(char *filename)
{
    int     fd;
    char    *line;
    t_env   *env;
    t_data  *data;

    open_file(filename, &fd);
    env = (t_env *)safe_malloc(1, sizeof(t_env));
    init_env(env);
    set_get_env(SET, env);
    data = NULL;
    set_get_data(SET, data);
    printf("** after init env **\n");
    print_env_data();
    while (1)
    {
        line = NULL;
        line = get_next_line(fd);
        if (line)
            make_information(line);
        else
            break ;
    }
}

void    make_information(char *line)
{
    char    **split;

    split = ft_split(line, SPACE);
    if (!split[0])
    {
        free(line);
        free(split[0]);
        free(split);
        return ;
    }
    if (check_first_element(split[0]) == ENV)
    {
        make_env_data(split);
        printf("\n** after read line **\n");
        print_env_data();
    }
    else if (check_first_element(split[0]) == OBJ)
    {
        // printf("make obj\n\n");
        // make_obj_data(split);
    }
    else
        print_error_and_exit("parser", "couldn't find identifier");
    free_split(split);
    free(line);
}

void    set_struct_xyz(t_xyz *xyz, double arr[3])
{
    xyz->x = arr[0];
    xyz->y = arr[1];
    xyz->z = arr[2];
}

void    set_array(char *str, double arr[3], int select)
{
    char    **number;
    int     i;
    int     count;

    i = -1;
    count = 0;
    while (str[++i])
    {
        if (str[i] == ',')
            count++;
    }
    if (count > 2)
        print_error_and_exit("set array", "too many \',\'"); 
    number = ft_split(str, ",");
    if (count_split(number) != 3)
        print_error_and_exit("set array", "argument count should be 3");
    arr[0] = ft_atof(number[0]);
    arr[1] = ft_atof(number[1]);
    arr[2] = ft_atof(number[2]);
    free_split(number);
    if (select == VECTOR || select == RGB)
        check_array_num(arr, select);
}
