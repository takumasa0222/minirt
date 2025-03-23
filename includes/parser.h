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
# define SPACE "\t\n\v\r\f "
# define ARGS "0123456789.,ACLsplcy"

enum {
    A,
    C,
    L,
    PL,
    SP,
    CY
};

//環境設定用のデータとオブジェクト用のデータを分ける
//環境設定用のデータは一つにまとめる
//flagでA,C,Lのデータ入力を監視し、2が入れば Error->終了
//color情報は一つにまとめる　https://harm-smits.github.io/42docs/libs/minilibx/colors.html
//vectorが(0,0,0)の場合は Error->終了

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

void    print_error_and_exit(char *func_name, char *message);
void    open_file(char *file_name, int *fd);
double  ft_atof(char *nptr);
void    *safe_malloc(size_t count, size_t size);
int     check_first_arg(char *str);
void    make_information(char *line);
void    parser(char *filename);
void	free_split(char **split);
unsigned int    make_trgb(double t, int r, int g, int b);

#endif
