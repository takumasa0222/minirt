#ifndef CALC_H
# define CALC_H

# include "parser.h"

// dot_cross.c
double   dot(t_xyz v1, t_xyz v2);
t_xyz   cross(t_xyz v1, t_xyz v2);

// multi_sub_vector.c
t_xyz   multi_v1_v2(t_xyz v1, t_xyz v2);
t_xyz   multi_v_f(t_xyz v, double f);
t_xyz   sub_v1_v2(t_xyz v1, t_xyz v2);
t_xyz   sub_v_f(t_xyz v, double f);

// plus_minus_vector.c


# endif