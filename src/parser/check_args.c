#include "parser.h"

int check_first_arg(char *str)
{
    if (!ft_memcmp(str, "A", 2) || !ft_memcmp(str, "C", 2)
        || !ft_memcmp(str, "L", 2))
        return (ENV);
    if (!ft_memcmp(str, "sp", 3) || !ft_memcmp(str, "pl", 3)
        || !ft_memcmp(str, "cy", 3))
        return (OBJ);
    return (FALSE);
}

int count_args(char **split)
{
    int i;

    i = 0;
    while (split[i])
        i++;
    return (i);
}

void    check_array_num(double arr[3], int select)
{
    if (select == VECTOR)
    {
        if (arr[0] == 0 && arr[1] == 0 && arr[2] == 0)
            print_error_and_exit("vector", "invalid vector(all nums are 0)");
        if (if_0_1(arr[0]) * if_0_1(arr[1]) * if_0_1(arr[2]) == 0)
            print_error_and_exit("vecort", "number is not between 0 and 1");
    }
    if (select == RGB)
    {
        if (if_0_255(arr[0]) * if_0_255(arr[1]) * if_0_255(arr[2]) == 0)
           print_error_and_exit("vecort", "number is not between 0 and 255"); 
    }
}

