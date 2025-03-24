#include "parser.h"

void    parser(char *filename)
{
    int     fd;
    char    *line;
    t_env   *env;

    open_file(filename, &fd);
    env = (t_env *)safe_malloc(1, sizeof(t_env));
    init_env(env);
    while (1)
    {
        line = NULL;
        line = get_next_line(fd);
        if (line)
            make_information(line, env);
        else
            break ;
    }
}

void    make_information(char *line, t_env *env)
{
    char    **split;

    split = ft_split(line, SPACE);
    // for (int i = 0; split[i]; i++) //splitデータ確認
    //     printf("%s\n", split[i]);
    if (!split[0])
    {
        free(line);
        free(split[0]);
        free(split);
        return ;
    }
    if (check_first_arg(split[0]) == ENV)
    {
        // printf("make env\n\n");
        make_env_data(split, env);
        printf("env->flag[A] = %d\n", env->flag[A]);
        printf("env->amb_trgb = %X\n", env->amb_trgb);
        exit(1);
    }
    else if (check_first_arg(split[0]) == OBJ)
    {
        printf("make obj\n\n");
        // make_obj_data(split);
    }
    else
    {
        print_error_and_exit("parser", "couldn't find identifier");
    }
    free_split(split);
    free(line);
}

int check_first_arg(char *str)
{
    if (!ft_memcmp(str, "A", 2) || !ft_memcmp(str, "C", 2)
        || !ft_memcmp(str, "L", 2))
        return (ENV);
    if (!ft_memcmp(str, "sp", 3) || !ft_memcmp(str, "pl", 3)
        || !ft_memcmp(str, "cy", 3))
        return (OBJ);
    return (FALSE);
}

void    set_amb_data(char **split, t_env *env)
{
    double  t;
    double  rgb[3];

    if (env->flag[A] == 1)
        print_error_and_exit("set_amb_data", "data already existed");
    env->flag[A] = 1;
    if (count_args(split) != 3)
        print_error_and_exit("set_amb_data", "number of arguments is not 3");
    t = ft_atof(split[1]);
    if (if_0_1(t) == false)
        print_error_and_exit("set_amb_data", "number is not between 0 and 1"); 
    set_array(split[2], rgb, RGB);
    env->amb_trgb = make_trgb(t, rgb[0], rgb[1], rgb[2]);
    return ;
}

void    make_env_data(char **split, t_env *env)
{
    if (ft_memcmp(split[0], "A", 2) == 0)
        set_amb_data(split, env);
    // else if (ft_memcmp(split[0], "C", 2) == 0)
    //     set_cam_data(split, env);
    // else
    //     set_light_data(split,env);
}

int count_args(char **split)
{
    int i;

    i = 0;
    while (split[i])
        i++;
    return (i);
}

void    check_array_num(double arr[3], int select)
{
    if (select == VECTOR)
    {
        if (arr[0] == 0 && arr[1] == 0 && arr[2] == 0)
            print_error_and_exit("vector", "invalid vector(all nums are 0)");
        if (if_0_1(arr[0]) * if_0_1(arr[1]) * if_0_1(arr[2]) == 0)
            print_error_and_exit("vecort", "number is not between 0 and 1");
    }
    if (select == RGB)
    {
        if (if_0_255(arr[0]) * if_0_255(arr[1]) * if_0_255(arr[2]) == 0)
           print_error_and_exit("vecort", "number is not between 0 and 255"); 
    }
}

void    set_array(char *str, double rgb[3], int select)
{
    char    **number;

    number = ft_split(str, ",");
    if (count_args(number) != 3)
        print_error_and_exit("set array", "argument count should be 3");
    rgb[0] = ft_atof(number[0]);
    rgb[1] = ft_atof(number[1]);
    rgb[2] = ft_atof(number[2]);
    free_split(number);
    check_array_num(rgb, select);
}
