#include "parser.h"

unsigned int    make_trgb(double t, int r, int g, int b)
{
    t = round(255 * t);
    return ((int)t << 24 | r << 16 | g << 8 | b);
}
