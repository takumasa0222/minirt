#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include "libft.h"

enum {
    AMBIENT,
    CAMERA,
    LIGHT,
    PLANE,
    SPHERE,
    CYLINDER
};

typedef struct s_data
{
    int             identifier;
    double          coordinate[3];
    double          vector[3];
    unsigned int    rgb[3];
    double          ratio;
    unsigned int    degree;
    double          diameter;
    double          height;
}  t_data;

void    print_error_and_exit(void);
void    open_file(char *file_name, int *fd);
char	*get_next_line(int fd);



#endif
