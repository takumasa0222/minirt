#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include <errno.h>
# include "libft.h"

# define MANDATORY 0
# define BONUS 1
# define SET 0
# define GET 1
# define ENV 0
# define LIT 1
# define OBJ 2
# define OTHER 3
# define VECTOR 4
# define RGB 5
# define SPACE "\t\n\v\r\f "

enum {
    A,
    C,
    L,
    PL,
    SP,
    CY
};

typedef struct s_xyx
{
    double  x;
    double  y;
    double  z;
}   t_xyz;

typedef struct s_lit
{
    int             flag;
    t_xyz           xyz;
    // int             trgb;
    double          t;
    t_xyz           rgb;
    struct s_lit    *next;
}   t_lit;

typedef struct s_env
{
    int             part;
    int             flag[3];
    // unsigned int    amb_trgb;
    double          amb_t;
    t_xyz           amb_rgb;
    t_xyz           cam_xyz;
    t_xyz           cam_vector;
    double          cam_degree;
    // t_xyz           light_xyz;
    // int             light_trgb;
    t_lit           *lit;
}   t_env;

typedef struct s_obj
{
    int             id;
    t_xyz           xyz;
    t_xyz           vector;
    // unsigned int    rgb;
    t_xyz           rgb;
    double          diameter;
    double          height;
    struct s_obj   *next;
}  t_obj;

//check_element.c
int             check_first_element(char *str);
int             count_split(char **split);
void            check_array_num(double arr[3], int select);
void            check_comma(char *str);

//check_range.c
bool            is_minus1_1(double num);
bool            is_0_1(double num);
bool            is_0_180(double num);
bool            is_0_255(double num);

//free.c
void	        free_split(char **split);
void	        free_lit(t_lit *lit);
void	        free_obj(t_obj *data);

//ft_atof.c
double          ft_atof(char *nptr);

//init.c
void            init_xyz(t_xyz *xyz);
void            init_env(t_env *env, t_lit *lit, int part);
void            init_lit(t_lit *lit);
void            init_obj(t_obj *obj);

//make_env_data.c
void            make_env_data(char **split);
void            set_amb_data(char **split, t_env *env);
void            set_cam_data(char **split, t_env *env);

//make_lit_data.c
void            make_lit_data(char **split);
void            set_lit_data(char **split, t_lit *lit, t_env *env);
void            lit_lst_add_back(t_lit *lit, t_lit *new);

//make_obj_data.c
void            make_obj_data(char **split);
void            set_pl_data(char **split, t_obj *new);
void            set_sp_data(char **split, t_obj *new);
void            set_cy_data(char **split, t_obj *new);
void            obj_lst_add_back(t_obj *obj, t_obj *new);

//parser.c
void            parser(char *filename, int part);
void            init_parser_data(t_env *env, t_lit *lit, t_obj *obj, int part);
void            make_information(char *line);
void            set_array(char *str, double arr[3], int select);
void            set_struct_xyz(t_xyz *xyz, double arr[3]);

//print_function.c
void            print_error_and_exit(char *func_name, char *message);
void            print_env_data(void);
void            print_lit_data(t_lit *lit);
void            print_obj_data(void);

//setter_getter.c
t_env           *set_get_env(int select, t_env *new);
t_lit           *set_get_lit(int select, t_lit *new);
t_obj           *set_get_obj(int select, t_obj *new);

//utils.c
void            open_file(char *file_name, int *fd);
void            *safe_malloc(size_t count, size_t size);
// unsigned int    make_trgb(double t, int r, int g, int b);
unsigned int    make_trgb(double t, double r, double g, double b);


#endif
