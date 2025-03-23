#include "parser.h"

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

void    free_split(char **split)
{
    int i;

    i = -1;
    while (split[++i])
        free(split[i]);
    free(split);
}

void    make_information(char *line)
{
    char    **split;

    split = ft_split(line, SPACE);
    for (int i = 0; split[i]; i++) //splitデータ確認
        printf("%s\n", split[i]);
    if (!split[0])
    {
        free(line);
        free(split[0]);
        free(split);
        return ;
    }
    if (check_first_arg(split[0]) == ENV)
    {
        printf("make env\n\n");
        //make_env_data(split);
    }
    else if (check_first_arg(split[0]) == OBJ)
    {
        //make_obj_data(split);
        printf("make obj\n\n");
    }
    else
    {
        print_error_and_exit("couldn't find identifier");
    }
    free_split(split);
    free(line);
}

void    parser(char *filename)
{
    int     fd;
    char    *line;

    open_file(filename, &fd);
    while (1)
    {
        line = NULL;
        line = get_next_line(fd);
        if (line)
        {
            make_information(line);
            // printf("%s", line);
        }
        else
            break ;
    }

}

unsigned int    make_trgb(double t, int r, int g, int b)
{
    t = round(255 * t);
    return ((int)t << 24 | r << 16 | g << 8 | b);
}

void    practice(void)
{
    t_env   *env;
    t_data  *data;
    t_data  *head;

    //A,C,L data
    env = (t_env *)malloc(sizeof(t_env));
    env->amb_trgb = make_trgb(0.2, 255, 255, 255);
    env->cam_xyz.x = -50;
    env->cam_xyz.y = 0;
    env->cam_xyz.z = 20;
    env->cam_vector.x = 0;
    env->cam_vector.y = 0;
    env->cam_vector.z = 1;
    env->cam_degree = 70;
    env->light_trgb = make_trgb(0.7, 255, 255, 255);
    env->light_xyz.x = -40;
    env->light_xyz.y = 0;
    env->light_xyz.z = 20;

    //pl data
    data = (t_data *)malloc(sizeof(t_data));
    head = data;
    data->id = PL;
    data->xyz.x = 0;
    data->xyz.y = 0;
    data->xyz.z = 0;
    data->vector.x = 0.1;
    data->vector.y = 0;
    data->vector.z = 0;
    data->rgb = make_trgb(0, 255, 0, 255);
    data->next = NULL;

    //sp data
    t_data *new1;
    new1 = (t_data *)malloc(sizeof(t_data));
    head->next = new1;
    new1->id = SP;
    new1->xyz.x = 0;
    new1->xyz.y = 0;
    new1->xyz.z = 20;
    new1->diameter = 20;
    new1->rgb = make_trgb(0, 255, 0, 0);
    new1->next = NULL;

    //cy data;
    t_data *new2;
    new2 = (t_data *)malloc(sizeof(t_data));
    head->next->next = new2;
    new2->id = CY;
    new2->xyz.x = 50.0;
    new2->xyz.y = 0.0;
    new2->xyz.z = 20.5;
    new2->vector.x = 0;
    new2->vector.y = 0;
    new2->vector.z = 1.0;
    new2->diameter = 14.2;
    new2->height = 21.42;
    new2->rgb = make_trgb(0, 10, 0, 255);

    printf("\nA:TRGB  = %X\n", env->amb_trgb);
    printf("C:xyz   = (%0.1f, %0.1f, %0.1f)\n", env->cam_xyz.x, env->cam_xyz.y, env->cam_xyz.z);
    printf(" :vector= (%0.1f, %0.1f, %0.1f)\n", env->cam_vector.x, env->cam_vector.y, env->cam_vector.z);
    printf("L:xyz   = (%0.1f, %0.1f, %0.1f)\n", env->light_xyz.x, env->light_xyz.y, env->light_xyz.z);
    printf(" :TRGB  = %X\n", env->light_trgb);
    printf("\n3 = pl, 4 = sp, 5 = cy\n");
    while (data)
    {
        printf("%d:xyz   = (%0.1f, %0.1f, %0.1f)\n", data->id, data->xyz.x, data->xyz.y, data->xyz.z);
        if (data->id == PL || data->id == CY)
            printf(" :vector= (%0.1f, %0.1f, %0.1f)\n", data->vector.x, data->vector.y, data->vector.z);
        printf(" :RGB   = %X\n", data->rgb);
        if (data->id == SP || data->id == CY)
            printf(" :diameter= %0.1f\n", data->diameter);
        if (data->id == CY)
            printf(" :height= %0.1f\n", data->height);
        data = data->next;
    }
    exit(1);
}

int main(int argc, char **argv)
{
    // t_env   *env;
    // t_data  *data;

    if (argc != 2)
        print_error_and_exit("there should be one argument");
    practice();
    // env = NULL;
    // data = NULL;
    parser(argv[1]);
    //minirt();
    // free(env);
    // free_data(data);
    return (0);
}