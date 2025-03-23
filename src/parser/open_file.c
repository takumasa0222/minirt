#include "parser.h"

void open_file(char *file_name, int *fd)
{
    *fd = open(file_name, O_RDONLY);
    if (*fd == -1)
        print_error_and_exit("open_file", "couldn't open file");
}
