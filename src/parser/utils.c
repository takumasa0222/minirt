#include "parser.h"

void open_file(char *file_name, int *fd)
{
    *fd = open(file_name, O_RDONLY);
    if (*fd == -1)
        print_error_and_exit("open_file", "couldn't open file");
}

void    *safe_malloc(size_t count, size_t size)
{
    void    *tmp;

    tmp = ft_calloc(size, count);
    if (!tmp)
        exit((ft_printf(2, "malloc: %s\n", strerror(errno)), EXIT_FAILURE));
    return (tmp);
}

// unsigned int    make_trgb(double t, int r, int g, int b)
unsigned int    make_trgb(double t, double r, double g, double b)
{
    t = round(255 * t);
    r = round(r);
    g = round(g);
    b = round(b);
    return ((int)t << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}
