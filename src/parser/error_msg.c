#include "parser.h"

void    print_error_and_exit(char *message)
{
    ft_printf(2, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}
