/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 05:15:35 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/12 14:43:31 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_minus1_1(double num)
{
	return (num >= -1.0 && num <= 1.0);
}

bool	is_0_1(double num)
{
	return (num >= 0.0 && num <= 1.0);
}

bool	is_0_180(double num)
{
	return (num >= 0.0 && num <= 180.0);
}

bool	is_0_255(double num)
{
	return (num >= 0.0 && num <= 255.0);
}
