#include "parser.h"

void    print_error_and_exit(void)
{
    printf("Error\n");
    exit(EXIT_FAILURE);
}

void open_file(char *file_name, int *fd)
{
    *fd = open(file_name, O_RDONLY);
    if (*fd == -1)
        print_error_and_exit();
}

// void    *safe_malloc(size_t count, size_t size)
// {
//     void    *tmp;

//     tmp = ft_calloc(size, count);
//     if (!tmp)
//         exit((ft_printf(2, "malloc: %s\n", strerror(errno)), EXIT_FAILURE));
//     return (tmp);
// }

int main(int argc, char **argv)
{
    int     fd;
    // t_env_data  env;
    // t_obj_data  *obj;
    char    *line;
    // t_data  *data;

    if (argc != 2)
        print_error_and_exit();
    open_file(argv[1], &fd);
    // data = safe_malloc(1, sizeof(t_data));
    while (1)
    {
        line = NULL;
        line = get_next_line(fd);
        if (line)
            printf("%s", line);
            //parser(line);
        else
            break ;
    }
    // free(data);
    return (0);
}