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
        print_error_and_exit();
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

int main(int argc, char **argv)
{
    // t_env   *env;
    // t_data  *data;

    if (argc != 2)
        print_error_and_exit();
    // env = NULL;
    // data = NULL;
    parser(argv[1]);
    //minirt();
    // free(env);
    // free_data(data);
    return (0);
}