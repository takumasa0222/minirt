#include "calc.h"

double   dot(t_xyz v1, t_xyz v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_xyz   cross(t_xyz v1, t_xyz v2)
{
    t_xyz   tmp;

    tmp.x = v1.y * v2.z - v1.z * v2.y;
    tmp.y = v1.z * v2.x - v1.x * v2.z;
    tmp.z = v1.x * v2.y - v1.y * v2.x;
    return (tmp);
}

void    calc_test()
{
    t_xyz   v1;
    t_xyz   v2;
    t_xyz   tmp;
    double  f = 3.0f;
    double  ans;

    v1.x = 1;
    v1.y = 1;
    v1.z = 1;
    v2.x = 2;
    v2.y = 2;
    v2.z = 2;
    printf("** calculator check **\n");
    printf("v1 = (1, 1, 1) v2 = (2, 2, 2) f = 3.0f\n");
    ans = dot(v1, v2);
    printf("dot(v1, v2) = %f\n", ans);
    tmp = cross(v1, v2);
    printf("cross(v1, v2) = (%f, %f, %f)\n", tmp.x, tmp.y, tmp.z);
    tmp = multi_v1_v2(v1, v2);
    printf("multi_v1_v2(v1, v2) = (%f, %f, %f)\n", tmp.x, tmp.y, tmp.z);
    tmp = multi_v_f(v1, f);
    printf("multi_v_f(v1, f) = (%f, %f, %f)\n", tmp.x, tmp.y, tmp.z);
    tmp = divid_v1_v2(v1, v2);
    printf("divid_v1_v2(v1, v2) = (%f, %f, %f)\n", tmp.x, tmp.y, tmp.z);
    tmp = divid_v_f(v1, f);
    printf("divid_v_f(v1, f) = (%f, %f, %f)\n", tmp.x, tmp.y, tmp.z);
    tmp = plus_v1_v2(v1, v2);
    printf("plus_v1_v2(v1, v2) = (%f, %f, %f)\n", tmp.x, tmp.y, tmp.z);
    tmp = plus_v_f(v1, f);
    printf("plus_v_f(v1, f) = (%f, %f, %f)\n", tmp.x, tmp.y, tmp.z);
    tmp = minus_v1_v2(v1, v2);
    printf("minus_v1_v2(v1, v2) = (%f, %f, %f)\n", tmp.x, tmp.y, tmp.z);
    tmp = minus_v_f(v1, f);
    printf("minus_v_f(v1, f) = (%f, %f, %f)\n", tmp.x, tmp.y, tmp.z);
    v1.x = 3;
    v1.y = 4;
    v1.z = 5;    
    printf("v1 = (3, 4, 5)\n");
    ans = sqr(v1.x);
    printf("sqr(v1.x) = %f\n", ans);
    ans = calc_length2(v1);
    printf("calc_length2(v1) = %f\n", ans);
    ans = calc_length(v1);
    printf("calc_length(v1) = %f\n", ans);
    tmp = normalize(v1);
    printf("normalize(v1) = (%f, %f, %f)\n", tmp.x, tmp.y, tmp.z);
}
