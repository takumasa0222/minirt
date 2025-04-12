#include "parser.h"
#include "ui.h"
#include "raytracing.h"
#include "calc.h"

void check_argv(int argc, char **argv)
{
    char    *filename;

    if (argc != 2)
        print_error_and_exit("main", "1 argument required");
    filename = argv[1];
    while (filename)
    {
        if (ft_memcmp(filename, "./", 2) == 0)
        filename += 2;
        else if (ft_memcmp(filename, "../", 3) == 0)
        filename += 3;
        else
        break;
    }
    while (*filename != '.')
    filename++;
    if (ft_memcmp(filename, ".rt", 4))
        print_error_and_exit("main", "*.rt file required");
}

int main(int argc, char **argv)
{
    int     part;
    t_env   *env;
    t_obj   *obj;

    check_argv(argc, argv);
    part = MANDATORY;
    parser(argv[1], part);
    env = set_get_env(GET, NULL);
    obj = set_get_obj(GET, NULL);
    // minirt(env, data);
    // minirt();
	init_window(obj, env);
    //free_lit(env->lit);
    //free(env);
    //free_obj(obj);
    calc_test();
    printf("end\n");
    return (0);
}