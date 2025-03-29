#include "calc.h"

double  sqr(double x)
{
    return (x * x);
}

double  calc_length2(t_xyz vector)
{
    return (sqr(vector.x) + sqr(vector.y) + sqr(vector.z));
}

double  calc_length(t_xyz vector)
{
    return (sqrt(calc_length2(vector)));
}

t_xyz   normalize(t_xyz vector)
{
    double  length;

    length = calc_length(vector);
    return (sub_v_f(vector, length));
}
