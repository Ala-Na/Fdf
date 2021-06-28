/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brasenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anadege <anadege@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:48:24 by anadege           #+#    #+#             */
/*   Updated: 2021/06/28 15:16:39 by anadege          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	brasenham_segment(int x_start, int y_start, int x_end, int y_end)
{
	int	error_margin;
	int	delta_x;
	int	delta_y;

	error_margin = x_end - x_start;
	delta_x = error_margin * 2;
	delta_y = (y_end - y_start) * 2;
	while (x_start < x_end)
	{
		x_start += 1;
		error_margin -= delta_y;
		if (error_margin <= 0)
		{
			y_start += 1;
			error_margin += delta_x;
		}
		//mlx_pixel_put(mlx, win, x_start, y_start, color);
	}
	return (0);
}
