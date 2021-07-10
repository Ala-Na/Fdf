/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:38:35 by anadege           #+#    #+#             */
/*   Updated: 2021/07/10 15:37:27 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_param *param)
{
	int	modif;

	modif = 0;
	if (keycode == 65307)
	{
		clean_exit(param);
		exit(0);
	}
	else if (keycode >= 65361 && keycode <= 65364)
	{
		if (keycode == 65364)
			modif = 60;
		else if (keycode == 65362)
			modif = -60;
		else if (keycode == 65363)
			modif = 30;
		else if (keycode == 65361)
			modif = -30;
		modify_position(param, modif);
	}
	else if (keycode == 32)
		erase_modifications(param);
	else if (keycode == 99)
		modify_perspective(param);
	return (0);
}
