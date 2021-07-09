/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 11:44:18 by anadege           #+#    #+#             */
/*   Updated: 2021/07/09 17:37:49 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	error_in_arguments(int argc)
{
	ft_putstr_fd("\nARGUMENTS ERROR\n\nTip : ", 1);
	ft_putnbr_fd(argc, 1);
	ft_putstr_fd(" arguments were given (instead of 2)\n\n", 1);
	return (1);
}

int	error_while_parsing(t_map *map)
{
	ft_putstr_fd("\nPARSING ERROR\n\nTip : Check your map\n\n", 1);
	if (map)
		free(map);
	return (1);
}

void	*init_error(char *str, t_param *param)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(" INITIALIZATION ERROR\n\n", 1);
	clean_exit(param);
	return (NULL);
}
