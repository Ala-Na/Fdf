/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 11:44:18 by anadege           #+#    #+#             */
/*   Updated: 2021/07/02 14:22:00 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error_in_arguments(int argc)
{
		ft_putstr_fd("Error in arguments : ", 1);
		ft_putnbr_fd(argc, 1);
		ft_putstr_fd(" given (should be 2)\n", 1);
		return (1);
}

int	error_while_parsing(t_map *map)
{
	ft_putstr_fd("Error while parsing\n", 1);
	if (map)
		free(map);
	return (1);
}
