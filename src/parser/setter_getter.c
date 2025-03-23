#include "parser.h"

t_env   *set_get_env(int select, t_env *new)
{
    static t_env *tmp;

    if (select == SET)
        tmp = new;
    return (tmp);
}

t_data  *set_get_data(int select, t_env *new)
{
    static t_env *tmp;

    if (select == SET)
        tmp = new;
    return (tmp);
}
