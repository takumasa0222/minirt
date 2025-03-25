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

# define SET 0
# define GET 1
# define ENV 0
# define OBJ 1
# define OTHER 2
# define VECTOR 3
# define RGB 4
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

typedef struct s_env
{
    int             flag[3];
    unsigned int    amb_trgb;
    t_xyz           cam_xyz;
    t_xyz           cam_vector;
    double          cam_degree;
    t_xyz           light_xyz;
    int             light_trgb;
}   t_env;

typedef struct s_data
{
    int             id;
    t_xyz           xyz;
    t_xyz           vector;
    unsigned int    rgb;
    double          diameter;
    double          height;
    struct s_data   *next;
}  t_data;

//check_element.c
int             check_first_element(char *str);
int             count_split(char **split);
void            check_array_num(double arr[3], int select);

//check_range.c
bool            is_minus1_1(double num);
bool            is_0_1(double num);
bool            is_0_180(double num);
bool            is_0_255(double num);

//free.c
void	        free_split(char **split);
void	        free_data(t_data *data);

//ft_atof.c
double          ft_atof(char *nptr);

//init.c
void            init_xyz(t_xyz *xyz);
void            init_env(t_env *env);
void            init_data(t_data *data);

//make_env_data.c
void            make_env_data(char **split);
void            set_amb_data(char **split, t_env *env);
void            set_cam_data(char **split, t_env *env);
void            set_light_data(char **split, t_env *env);

//make_obj_data.c
void            make_obj_data(char **split);
void            set_pl_data(char **split, t_data *data);
void            set_sp_data(char **split, t_data *data);
void            set_cy_data(char **split, t_data *data);
void            lst_add_back(t_data *data, t_data *new);

//parser.c
void            parser(char *filename);
void            make_information(char *line);
void            set_array(char *str, double arr[3], int select);
void            set_struct_xyz(t_xyz *xyz, double arr[3]);

//print_function.c
void            print_error_and_exit(char *func_name, char *message);
void            print_env_data(void);
void            print_obj_data(void);

//setter_getter.c
t_env           *set_get_env(int select, t_env *new);
t_data          *set_get_data(int select, t_data *new);

//utils.c
void            open_file(char *file_name, int *fd);
void            *safe_malloc(size_t count, size_t size);
unsigned int    make_trgb(double t, int r, int g, int b);

#endif
