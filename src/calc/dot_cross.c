#include "cal.h"

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
