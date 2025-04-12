/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 05:29:01 by yotsurud          #+#    #+#             */
/*   Updated: 2025-04-12 05:29:01 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

double  sqr(double x)
{
    return (x * x);
}

double  calc_length2(t_xyz vector)
{
    return (sqr(vector.x) + sqr(vector.y) + sqr(vector.z));
}

double  calc_length(t_xyz vector)
{
    return (sqrt(calc_length2(vector)));
}

t_xyz   normalize(t_xyz vector)
{
    double  length;

    length = calc_length(vector);
    return (divid_v_f(vector, length));
}
