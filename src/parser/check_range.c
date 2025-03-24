#include "parser.h"

bool    if_minus1_1(double num)
{
    return (num >= -1.0 && num <= 1.0);
}

bool    if_0_1(double num)
{
    return (num >= 0.0 && num <= 1.0);
}

bool    if_0_180(double num)
{
    return (num >= 0 && num <= 180);
}

bool    if_0_255(double num)
{
    return (num >= 0 && num <= 255);
}
