#include "parser.h"

void    print_error_and_exit(char *func_name, char *message)
{
    ft_printf(2, "Error: %s: %s\n", func_name, message);
    exit(EXIT_FAILURE);
}
