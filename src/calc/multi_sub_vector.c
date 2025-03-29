#include "calc.h"

t_xyz   multi_v1_v2(t_xyz v1, t_xyz v2)
{
    t_xyz   tmp;

    tmp.x = v1.x * v2.x;
    tmp.y = v1.y * v2.y;
    tmp.z = v1.z * v2.z;
    return (tmp);
}

t_xyz   multi_v_f(t_xyz v, double f)
{
    t_xyz   tmp;

    tmp.x = v.x * f;
    tmp.y = v.y * f;
    tmp.z = v.z * f;
    return (tmp);
}

t_xyz   sub_v1_v2(t_xyz v1, t_xyz v2)
{
    t_xyz   tmp;

    // v2の要素に0が含まれていた場合の処理
    tmp.x = v1.x / v2.x;
    tmp.y = v1.y / v2.y;
    tmp.z = v1.z / v2.z;
    return (tmp);
}

t_xyz   sub_v_f(t_xyz v, double f)
{
    t_xyz   tmp;

    // f = 0の場合の処理
    tmp.x = v.x / f;
    tmp.y = v.y / f;
    tmp.z = v.z / f;
    return (tmp);
}
