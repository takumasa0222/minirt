/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsurud <yotsurud@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 05:21:34 by yotsurud          #+#    #+#             */
/*   Updated: 2025/04/12 15:03:36 by yotsurud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_error_and_exit(char *func_name, char *message)
{
	ft_printf(2, "Error: %s: %s\n", func_name, message);
	exit(EXIT_FAILURE);
}
