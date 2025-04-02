#include "parser.h"
#include "ui.h"
#include "raytracing.h"
#include "calc.h"

void    minirt(void)
{
    t_env   *env;
    t_lit   *lit = NULL;
    t_obj  *data;
    t_obj  *head;

    //A,C,L data
    env = NULL;
    env = (t_env *)malloc(sizeof(t_env));
    lit = (t_lit *)malloc(sizeof(t_lit));
    env->amb_trgb = make_trgb(0.2, 255, 255, 255);
    env->cam_xyz.x = -50;
    env->cam_xyz.y = 0;
    env->cam_xyz.z = 20;
    env->cam_vector.x = 0;
    env->cam_vector.y = 0;
    env->cam_vector.z = 1;
    env->cam_degree = 70;
    lit->trgb = make_trgb(0.7, 255, 255, 255);
    lit->xyz.x = -40;
    lit->xyz.y = 0;
    lit->xyz.z = 20;

    //pl data
    data = (t_obj *)malloc(sizeof(t_obj));
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
    t_obj *new1;
    new1 = (t_obj *)malloc(sizeof(t_obj));
    head->next = new1;
    new1->id = SP;
    new1->xyz.x = 0;
    new1->xyz.y = 0;
    new1->xyz.z = 20;
    new1->diameter = 20;
    new1->rgb = make_trgb(0, 255, 0, 0);
    new1->next = NULL;

    //cy data;
    t_obj *new2;
    new2 = (t_obj *)malloc(sizeof(t_obj));
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
    printf("L:xyz   = (%0.1f, %0.1f, %0.1f)\n", lit->xyz.x, lit->xyz.y, lit->xyz.z);
    printf(" :TRGB  = %X\n", lit->trgb);
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

bool check_filename(char *filename)
{
    while (*filename != '.')
        filename++;
    if (ft_memcmp(filename, ".rt", 4))
        return (false);
    return (true);
}

int main(int argc, char **argv)
{
    int     part;
    t_env   *env;
    t_obj   *obj;

    if (argc != 2 || check_filename(argv[1]) == false)
        print_error_and_exit("main", "*.rt file required");
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