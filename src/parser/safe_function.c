#include "parser.h"

void    *safe_malloc(size_t count, size_t size)
{
    void    *tmp;

    tmp = ft_calloc(size, count);
    if (!tmp)
        exit((ft_printf(2, "malloc: %s\n", strerror(errno)), EXIT_FAILURE));
    return (tmp);
}