#ifndef CALC_H
# define CALC_H

# include "parser.h"

// dot_cross.c
double  dot(t_xyz v1, t_xyz v2);
t_xyz   cross(t_xyz v1, t_xyz v2);
void    calc_test();

// multi_sub_vector.c
t_xyz   multi_v1_v2(t_xyz v1, t_xyz v2);
t_xyz   multi_v_f(t_xyz v, double f);
t_xyz   divid_v1_v2(t_xyz v1, t_xyz v2);
t_xyz   divid_v_f(t_xyz v, double f);

// plus_minus_vector.c
t_xyz   plus_v1_v2(t_xyz v1, t_xyz v2);
t_xyz   plus_v_f(t_xyz v, double f);
t_xyz   minus_v1_v2(t_xyz v1, t_xyz v2);
t_xyz   minus_v_f(t_xyz v, double f);

// normalize.c
double  sqr(double x);
double  calc_length2(t_xyz vector);
double  calc_length(t_xyz vector);
t_xyz   normalize(t_xyz vector);

# endif